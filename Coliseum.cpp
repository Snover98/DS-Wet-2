//
// Created by oded on 30/11/17.
//
#include <cstdlib>
#include "Coliseum.h"

using namespace DSExceptions;

//functor for putting gladiator ids into an array
template<class T>
class putGladiatorsIdsIntoArray : public Func<T>{
private:
    int array_size;
    int current_empty_index;
    int* id_array;
public:
    putGladiatorsIdsIntoArray(int n, int* arr):array_size(n), current_empty_index(0), id_array(arr){}

    void operator()(T& glad) {
        //if the array is not full
        if(current_empty_index < array_size){
            //add the gladiator into the array
            id_array[current_empty_index] = glad.getID();
            //increase the index
            current_empty_index++;
        }
    }
};

//functor for separating the gladaitors into 2 arrays by a stimulant code
template<class T>
class separateGladsByStimulantCode : public Func<T>{
private:
    int stimulant_code;
    Gladiator** stimulated;
    Gladiator** unchanged;
    int stimulated_num;
    int unchanged_num;

public:
    separateGladsByStimulantCode(Gladiator** stim, Gladiator** u_c, int s_code):
            stimulant_code(s_code), stimulated(stim), unchanged(u_c), stimulated_num(0), unchanged_num(0){}

    void operator()(Gladiator& glad) {
        //check if the code works for the gladiator
        if(glad.getID()%stimulant_code == 0){
            //if it does, add him to the stimulated array
            stimulated[stimulated_num] = &glad;
            stimulated_num++;
        } else{
            //if it doesn't, add him to the unchanged array
            unchanged[unchanged_num] = &glad;
            unchanged_num++;
        }
    }

    int getStimulatedNum() const{
        return stimulated_num;
    }

    int getUnchangedNum() const{
        return unchanged_num;
    }
};

Coliseum::Coliseum(): top_gladiator(NULL), gladiators_num(0),
                      splay_glads_id(NULL), splay_glads_lvl(NULL),
                      trainers_list(NULL){
    //build the trees
    CompGladsByID<Gladiator>* comp_id =  new CompGladsByID<Gladiator>();
    CompGladsByLevel<Gladiator>* comp_lv = new CompGladsByLevel<Gladiator>();
    splay_glads_id = new SplayTree<Gladiator>(comp_id);
    splay_glads_id = new SplayTree<Gladiator>(comp_lv);
    trainers_list = new List<Trainer>();
}

Coliseum::~Coliseum() {
    //delete the level tree
    delete splay_glads_id;
    //delete the list and trainers within
    delete trainers_list;

    //delete the gladiators too
    splay_glads_id->removeAllAndDeleteInfo();
    //delete the last tree
    delete splay_glads_id;
}

void Coliseum::AddTrainerToColiseum(int trainerID) {
    //if there are no trainers
    if(trainers_list->getSize() == 0){
        trainers_list->insert(new Trainer(trainerID));
        return;
    }

    //find where the trainer should be
    List<Trainer>::Iterator it = trainers_list->begin();
    while(it != trainers_list->end() && (*it).getID()<trainerID){
        ++it;
    }

    //if we got to the end of the list - the trainer is not found, so we add him
    if(it == trainers_list->end()) {
        trainers_list->insert(new Trainer(trainerID), it);
        return;
    }

    //check if the trainer is already in
    if((*it).getID() == trainerID) {
        throw TrainerAlreadyIn();
    }

    //insert the trainer in the correct place
    trainers_list->insert(new Trainer(trainerID), it);
}

void Coliseum::AddGladiatorToColiseum(int gladiatorID, int trainerID, int level) {

    //find the gladiator's trainer
    List<Trainer>::Iterator it = trainers_list->begin();
    while(it != trainers_list->end() && (*it).getID()<trainerID){
        ++it;
    }

    //if the trainer was not found
    if(it==trainers_list->end() || (*it).getID()>trainerID){
        throw TrainerNotFound();
    }

    //create the new gladiator
    Gladiator* new_gladiator = new Gladiator(gladiatorID,level,*(it));

    //check if it's already in
    Gladiator* found_glad = splay_glads_id->find(*new_gladiator);
    if(found_glad != NULL && found_glad->getID()==gladiatorID){
        delete new_gladiator;
        throw GladiatorAlreadyIn();
    }

    //comparer by level
    CompGladsByLevel<Gladiator> comp_lv = CompGladsByLevel<Gladiator>();

    //check if the new gladiator has a higher level than the top gladiator
    if(top_gladiator == NULL || comp_lv(*new_gladiator, *top_gladiator) > 0){
        top_gladiator = new_gladiator;
    }

    //add the gladiator to the trees
    splay_glads_id->insert(*new_gladiator);
    splay_glads_id->insert(*new_gladiator);
    (*it).addGladiator(*new_gladiator);
    //update the number of gladiators
    gladiators_num++;
}

void Coliseum::FreeGladiatorFromColiseum(int gladiatorID) {
    //find the gladiator using a dummy with the same ID
    Gladiator dummy = Gladiator(gladiatorID);
    Gladiator* glad = (splay_glads_id->find(dummy));

    //if no gladiator was found
    if(glad == NULL || glad->getID() != gladiatorID){
        throw GladiatorNotFound();
    }

    //check the gladiator's trainer
    Trainer& trainer = (*glad).getTrainer();

    //remove the gladiator from his trainer's tree
    trainer.removeGladiator(*glad);

    //comparer by level
    CompGladsByLevel<Gladiator> comp_lv = CompGladsByLevel<Gladiator>();

    //if we are freeing the only gladiator
    if(gladiators_num == 1){
        top_gladiator = NULL;
    } else if(comp_lv(*top_gladiator, *glad) == 0) {
        //if the gladiator we are removing is the top gladiator
        List<Trainer>::Iterator it = trainers_list->begin();
        top_gladiator = (*it).getTopGladiator();

        //check the top gladiator of each trainer
        while(it != trainers_list->end()){
            if((*it).getTopGladiator() != NULL &&
                    (top_gladiator == NULL || comp_lv(*((*it).getTopGladiator()), *top_gladiator) > 0)){
                top_gladiator = (*it).getTopGladiator();
            }
            it++;
        }
    }

    //remove the gladiator from the level tree
    splay_glads_id->remove(*glad);

    //remove the gladiator from the ID tree
    splay_glads_id->remove(*glad);

    //delete the gladiator and update the number of gladiators
    delete glad;
    --gladiators_num;
}

void Coliseum::LevelUpGladiatorInColiseum(int gladiatorID, int level_increase) {
    //find the gladiator using a dummy with the same ID
    Gladiator dummy = Gladiator(gladiatorID);
    Gladiator* gladiator = splay_glads_id->find(dummy);

    //if the gladiator was found
    if(gladiator == NULL || gladiator->getID() != gladiatorID){
        throw GladiatorNotFound();
    }

    //remove the gladiator from the trees sorted by level
    splay_glads_id->remove(*gladiator);
    gladiator->getTrainer().removeGladiator(*gladiator);

    //change the gladiator's level
    gladiator->setLevel(gladiator->getLevel()+level_increase);

    //put him back in the level trees
    splay_glads_id->insert(*gladiator);
    gladiator->getTrainer().addGladiator(*gladiator);

    //comparer by level
    CompGladsByLevel<Gladiator> comp_lv = CompGladsByLevel<Gladiator>();

    //check if the new gladiator has a higher level than the top gladiator
    if(top_gladiator == NULL || comp_lv(*gladiator, *top_gladiator) > 0){
        top_gladiator = gladiator;
    }
}

Gladiator& Coliseum::GetTopGladiator() {
    //check if there are any gladiators
    if(gladiators_num == 0) {
        throw ColiseumIsEmpty();
    }
    return *top_gladiator;
}

int Coliseum::getTopGladiatorInTrainer(int trainerID) {

    List<Trainer>::Iterator it = trainers_list->begin();

    while(it != trainers_list->end()){
        if((*it).getID() == trainerID) {
            if((*it).getNumOfGladiators() == 0) {
                return -1;
            } else {
                return (*it).getTopGladiator()->getID();
            }
        }
        ++it;
    }

    throw TrainerNotFound();
}

void Coliseum::getColiseumGladiatorsByLevel(int trainerID, int **gladiators,
                                            int *num_of_gladiator) {
    //if the id is negative
    if(trainerID < 0) {
        //set num_of_gladiator into the number of all of the gladiators
        *num_of_gladiator = gladiators_num;

        //check if there are any gladiators
        if(*num_of_gladiator == 0){
            //set the array as NULL
            *gladiators = NULL;
            return;
        }

        //allocate the array accordingly
        *gladiators = (int*)malloc(sizeof(int)*(*num_of_gladiator));
        //check if the allocation was successful
        if(*gladiators == NULL){
            throw std::bad_alloc();
        }
        //put the gladiators in the array
        putGladiatorsIdsIntoArray<Gladiator> put_ids =
                putGladiatorsIdsIntoArray<Gladiator>(*num_of_gladiator,  *gladiators);

        splay_glads_id->InverseOrder(put_ids);
    } else {    //find the trainer with the inputted id
        List<Trainer>::Iterator it = trainers_list->begin();

        while(it != trainers_list->end()){
            //if the trainer was fiund
            if((*it).getID() == trainerID) {
                //if the trainer has no gladiators
                if((*it).getNumOfGladiators() == 0) {
                    //set the number as 0 and set the array as NULL
                    *num_of_gladiator = 0;
                    *gladiators = NULL;
                    return;
                } else {
                    //set num_of_gladiator into the number of gladiators the trainer has
                    *num_of_gladiator = (*it).getNumOfGladiators();
                    //allocate the array accordingly
                    *gladiators = (int*)malloc(sizeof(int)*(*num_of_gladiator));
                    //check if the allocation was successful
                    if(*gladiators == NULL){
                        throw std::bad_alloc();
                    }
                    //put the gladiators in the array
                    putGladiatorsIdsIntoArray<Gladiator> put_ids =
                            putGladiatorsIdsIntoArray<Gladiator>(*num_of_gladiator,  *gladiators);
                    (*it).getGladiators().InverseOrder(put_ids);
                    return;
                }
            }
            ++it;
        }
        //if the trainer was not found
        throw TrainerNotFound();
    }
}

void Coliseum::UpgradeGladiatorIDInColiseum(int gladiatorID, int upgradedID) {
    //check if the ID is already in use with the help of a dummy
    Gladiator dummy = Gladiator(upgradedID);
    if(gladiatorID == upgradedID || splay_glads_id->find(dummy) != NULL){
        throw GladiatorUpgradedIDAlreadyExist();
    }

    //find the gladiator we want to change using the dummy
    dummy.setID(gladiatorID);
    Gladiator* gladiator = splay_glads_id->find(dummy);

    //check if there is a gladiator with that ID in the system
    if(gladiator == NULL){
        throw GladiatorNotFound();
    }

    //remove the gladiator from the trees
    splay_glads_id->remove(*gladiator);
    splay_glads_id->remove(*gladiator);
    gladiator->getTrainer().removeGladiator(*gladiator);

    //update the gladiator's ID
    gladiator->setID(upgradedID);

    //put the gladiator back in the trees
    splay_glads_id->insert(*gladiator);
    splay_glads_id->insert(*gladiator);
    gladiator->getTrainer().addGladiator(*gladiator);
}

void Coliseum::mergeGladiatorsArrays(Gladiator** arr1, int size1,
                              Gladiator** arr2, int size2, Gladiator** new_arr) {

    //merge two sorted arrays
    int arr1Counter = 0;
    int arr2Counter = 0;
    int i;

    //comparer by level
    CompGladsByLevel<Gladiator> comp_lv = CompGladsByLevel<Gladiator>();

    //iterate on both arrays
    for(i=0; i<(size1+size2);i++) {
        //if one of the arrays has been fully done
        if(arr1Counter == size1 || arr2Counter == size2){
            break;
        }

        //if arr[i] has a bigger value than arr[j]
        if(comp_lv(*arr1[arr1Counter], *arr2[arr2Counter]) >= 0){
            new_arr[i] = arr1[arr1Counter];
            arr1Counter++;
        } else{
            new_arr[i] = arr2[arr2Counter];
            arr2Counter++;
        }
    }

    //until the remaining array is done, fill the new array
    while(arr1Counter < size1 || arr2Counter < size2) {
        if(arr1Counter < size1) {
            new_arr[i] = arr1[arr1Counter];
            arr1Counter++;
        } else {
            new_arr[i] = arr2[arr2Counter];
            arr2Counter++;
        }
        i++;
    }
}

void Coliseum::emptyLevelTrees(){
    //empty global level tree
    splay_glads_id->removeAll();

    //for each trainer empty his level tree
    List<Trainer>::Iterator it = trainers_list->begin();
    while(it != trainers_list->end()){
        (*it).emptyTree();
        ++it;
    }
}

void Coliseum::UpdateLevelsInColiseum(int stimulantCode, int stimulantFactor) {
    //checks if there are no gladiators in the coliseum
    if(gladiators_num == 0) {
        return;
    }

    //allocate all needed arrays
    Gladiator** stimulated = new Gladiator*[gladiators_num];
    Gladiator** unchanged = new Gladiator*[gladiators_num];
    Gladiator** sorted = new Gladiator*[gladiators_num];

    //create the function object
    separateGladsByStimulantCode<Gladiator> separate =
            separateGladsByStimulantCode<Gladiator>(stimulated, unchanged, stimulantCode);
    //use the function in inverse order
    splay_glads_id->InverseOrder(separate);

    //get array sizes
    int num_stim = separate.getStimulatedNum();
    int num_same = separate.getUnchangedNum();

    //empty the level trees
    emptyLevelTrees();

    //change the levels
    for(int i=0; i<num_stim; i++){
        stimulated[i]->setLevel(stimulantFactor*(stimulated[i]->getLevel()));
    }

    //merge the arrays into one big sorted array
    mergeGladiatorsArrays(stimulated, num_stim, unchanged, num_same, sorted);

    //put the gladiators back in
    for(int i=0; i<gladiators_num; i++){
        splay_glads_id->insert(*sorted[i]);
        //we do this because the actual trainer should not be changed
        sorted[i]->getTrainer().addGladiator(*sorted[i]);
    }

    //update top gladiator
    top_gladiator = sorted[0];

    //delete all allocated arrays
    delete[] stimulated;
    delete[] unchanged;
    delete[] sorted;
}



