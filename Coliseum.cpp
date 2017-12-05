//
// Created by oded on 30/11/17.
//
#include <cstdlib>
#include "Coliseum.h"
#include <new>
using namespace DSExceptions;


class putGladiatorsIdsIntoArray{
private:
    int array_size;
    int current_empty_index;
    int* array;
public:
    putGladiatorsIdsIntoArray(int n, int* arr):array_size(n), current_empty_index(n-1), array(arr){}

    void operator()(Gladiator& glad){
        //if the array is not full
        if(current_empty_index >= 0){
            //add the gladiator into the array
            array[current_empty_index] = glad.getID();
            //increase the index
            current_empty_index++;
        }
    }
};

class separateGladsByStimulantCode{
private:
    int stimulant_code;
    Gladiator* stimulated;
    Gladiator* unchanged;
    int stimulated_num;
    int unchanged_num;

public:
    separateGladsByStimulantCode(Gladiator* stim, Gladiator* u_c, int s_code):
            stimulant_code(s_code), stimulated(stim), unchanged(u_c), stimulated_num(0), unchanged_num(0){}

    void operator()(Gladiator& glad){
        if(glad.getID()%stimulant_code == 0){
            stimulated[stimulated_num] = glad;
            stimulated_num++;
        } else{
            unchanged[unchanged_num] = glad;
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

Coliseum::~Coliseum() {
    splayGladsLvl.removeAllAndDeleteInfo();
    splayGladsId.removeAll();

    List<Trainer>::Iterator it = trainersList.begin();

    while(it != trainersList.end()){
        (*it).getGladiators().removeAll();
        trainersList.remove(it);
        it=trainersList.begin();
    }
}

void Coliseum::AddTrainerToColiseum(int trainerID) {
    //if there are no trainers
    if(trainersList.getSize() == 0){
        trainersList.insert(Trainer(trainerID));
        return;
    }

    //find where the trainer should be
    List<Trainer>::Iterator it = trainersList.begin();
    while((*it).getID()<trainerID){
        it++;
    }

    //check if the trainer is already in
    if((*it).getID()==trainerID) {
        throw TrainerAlreadyIn();
    }

    //insert the trainer in the correct place
    trainersList.insert(Trainer(trainerID), it);
}


void Coliseum::AddGladiatorToColiseum(int gladiatorID, int trainerID, int level) {
    //find the gladiator's trainer
    List<Trainer>::Iterator it = trainersList.begin();
    while((*it).getID()<trainerID){
        it++;
    }

    //if the trainer was not found
    if(it==trainersList.end()){
        throw TrainerNotFound();
    }

    List<Trainer>::Iterator p = it;

    //create the new gladiator
    Gladiator* new_gladiator = new Gladiator(gladiatorID,level,*(it));

    //check if it's already in
    if(splayGladsId.find(*new_gladiator)){
        throw GladiatorAlreadyIn();
    }

    //check if the new gladiator has a higher level than the top gladiator
    if(level>topGladiator->getLevel()){
        topGladiator = new_gladiator;
    }

    //add the gladiator to the trees
    splayGladsId.insert(*new_gladiator);
    splayGladsLvl.insert(*new_gladiator);

    //update the number of gladiators
    gladiatorsNum++;
}

void Coliseum::FreeGladiatorFromColiseum(int gladiatorID) {
    //find the gladiator using a dummy with the same ID
    Gladiator dummy = Gladiator(gladiatorID);
    Gladiator* glad = (splayGladsId.find(dummy));

    //if no gladiator was found
    if(glad == NULL){
        throw GladiatorNotFound();
    }

    //check the gladiator's trainer
    Trainer& trainer = (*glad).getTrainer();

    //remove the gladiator from his trainer's tree
    trainer.removeGladiator(*glad);

    //if we are freeing the only gladiator
    if(gladiatorsNum == 1){
        topGladiator = NULL;
    } else if(CompGladsByLevel::operator()(*topGladiator, *glad) == 0) {
        //if the gladiator we are removing is the top gladiator
        List<Trainer>::Iterator it = trainersList.begin();
        topGladiator = (*it).getTopGladiator();

        while(it != trainersList.end()){
            if(topGladiator == NULL || (*it).getTopGladiator()->getLevel() > topGladiator->getLevel()) {
                topGladiator = (*it).getTopGladiator();
            }
            it++;
        }
    }

    //remove the gladiator from the level tree
    splayGladsLvl.remove(*glad);

    //remove the gladiator from the ID tree
    splayGladsId.remove(*glad);

    //delete the gladiator and update the number of gladiators
    delete glad;
    --gladiatorsNum;
}

void Coliseum::LevelUpGladiatorInColiseum(int gladiatorID, int levelIncrease) {
    //find the gladiator using a dummy with the same ID
    Gladiator dummy = Gladiator(gladiatorID);
    Gladiator* gladiator = splayGladsId.find(dummy);

    //if no gladiator was found
    if(gladiator == NULL){
        throw GladiatorNotFound();
    }

    //remove the gladiator from the trees sorted by level
    splayGladsLvl.remove(*gladiator);
    gladiator->getTrainer().getGladiators().remove(*gladiator);

    //change the gladiator's level
    gladiator->setLevel(gladiator->getLevel()+levelIncrease);

    //put hum back in the level trees
    splayGladsLvl.insert(*gladiator);
    gladiator->getTrainer().getGladiators().insert(*gladiator);
}

Gladiator& Coliseum::GetTopGladiator() {
    return *topGladiator;
}

int Coliseum::getGladiatorsNum() {
    return gladiatorsNum;
}

//@TODO change name to get
int Coliseum::FindTopGladiatorInTrainer(int trainerID) {
    List<Trainer>::Iterator it = trainersList.begin();

    while(it != trainersList.end()){
        if((*it).getID() == trainerID) {
            if((*it).getNumOfGladiators() == 0) {
                return -1;
            } else {
                return (*it).getTopGladiator()->getID();
            }
        }
    }

    throw TrainerNotFound();
}

void Coliseum::getColiseumGladiatorsByLevel(int trainerID, int **gladiators,
                                            int *numOfGladiator) {
    //if the id is negative
    if(trainerID < 0) {
        //set numOfGladiator into the number of all of the gladiators
        *numOfGladiator = getGladiatorsNum();
        //allocate the array accordingly
        *gladiators = (int*)malloc(sizeof(int)*(*numOfGladiator));
        //check if the allocation was successful
        if(*gladiators == NULL){
            throw std::bad_alloc();
        }
        //put the gladiators in the array
        splayGladsLvl.InverseOrder(putGladiatorsIdsIntoArray(*numOfGladiator, *gladiators));
    } else {
        List<Trainer>::Iterator it = trainersList.begin();

        while(it != trainersList.end()){
            if((*it).getID() == trainerID) {
                //if the trainer has no gladiators
                if((*it).getNumOfGladiators() == 0) {
                    //set the number as 0 and set the array as NULL
                    *numOfGladiator = 0;
                    *gladiators = NULL;
                    return;
                } else {
                    //set numOfGladiator into the number of gladiators the trainer has
                    *numOfGladiator = (*it).getNumOfGladiators();
                    //allocate the array accordingly
                    *gladiators = (int*)malloc(sizeof(int)*(*numOfGladiator));
                    //check if the allocation was successful
                    if(*gladiators == NULL){
                        throw std::bad_alloc();
                    }
                    //put the gladiators in the array
                    (*it).getGladiators().InverseOrder(putGladiatorsIdsIntoArray(*numOfGladiator, *gladiators));
                    return;
                }
            }
        }

        throw TrainerNotFound();
    }
}

void Coliseum::UpgradeGladiatorIDInColiseum(int gladiatorID, int upgradedID) {
    //check if the ID is already in use with the help of a dummy
    Gladiator dummy = Gladiator(upgradedID);
    if(splayGladsId.find(dummy) != NULL){
        throw GladiatorUpgradedIDAlreadyExist();
    }

    //find the gladiator we want to change using the dummy
    dummy.setID(gladiatorID);
    Gladiator* gladiator = splayGladsId.find(dummy);

    //check if there is a gladiator with that ID in the system
    if(gladiator == NULL){
        throw GladiatorNotFound();
    }

    //remove the gladiator from the trees
    splayGladsLvl.remove(*gladiator);
    splayGladsId.remove(*gladiator);
    gladiator->getTrainer().removeGladiator(*gladiator);

    //update the gladiator's ID
    gladiator->setID(upgradedID);

    //put the gladiator back in the trees
    splayGladsId.insert(*gladiator);
    splayGladsLvl.insert(*gladiator);
    gladiator->getTrainer().addGladiator(*gladiator);
}

void Coliseum::mergeGladiatorsArrays(Gladiator* arr1, int size1,
                              Gladiator* arr2, int size2, Gladiator* newArr) {
    //merge two sorted arrays
    int arr1Counter = 0;
    int arr2Counter = 0;
    int i;

    //iterate on both arrays
    for(i=0; i<(size1+size2);i++) {
        //if one of the arrays is empty
        if(arr1Counter == (size1-1) || arr2Counter == (size2-1)){
            break;
        }
        if(CompGladsByLevel::operator()(arr1[arr1Counter], arr2[arr2Counter]) <= 0){
            newArr[i] = arr1[arr1Counter];
            arr1Counter++;
        } else{
            newArr[i] = arr2[arr2Counter];
            arr2Counter++;
        }
    }

    while(arr1Counter < size1 || (arr2Counter < size2) {
        if(arr1Counter < (size1-1)) {
            newArr[i] = arr1[arr1Counter];
            arr1Counter++;
        } else {
            newArr[i] = arr2[arr2Counter];
            arr2Counter++;
        }
        i++;
    }
}

void Coliseum::emptyLevelTrees(){
    //empty global level tree
    splayGladsLvl.removeAll();

    //for each trainer empty his level tree
    List<Trainer>::Iterator it = trainersList.begin();
    while(it != trainersList.end()){
        (*it).getGladiators().removeAll();
        ++it;
    }
}

void Coliseum::UpdateLevelsInColiseum(int stimulantCode, int stimulantFactor) {
    //allocate all needed arrays
    Gladiator* stimulated = new Gladiator[gladiatorsNum];
    Gladiator* unchanged = new Gladiator[gladiatorsNum];
    Gladiator* sorted = new Gladiator[gladiatorsNum];

    //create the function object
    separateGladsByStimulantCode separate = separateGladsByStimulantCode(stimulated, unchanged, stimulantCode);
    //use the function in inverse order
    splayGladsLvl.InverseOrder(separate);

    //get array sizes
    int num_stim = separate.getStimulatedNum();
    int num_same = separate.getUnchangedNum();

    //empty the level trees
    emptyLevelTrees();

    //change the levels
    for(int i=0; i<num_stim; i++){
        stimulated[i].setLevel(stimulantFactor*(stimulated[i].getLevel()));
    }

    //merge the arrays into one big sorted array
    mergeGladiatorsArrays(stimulated, num_stim, unchanged, num_same, sorted);

    //put the gladiators back in
    for(int i=0; i<gladiatorsNum; i++){
        splayGladsLvl.insert(sorted[i]);
        //we do this because the actual trainer should not be changed
        sorted[i].getTrainer().getGladiators().insert(sorted[i]);
    }

    //delete all allocated arrays
    delete stimulated;
    delete unchanged;
    delete sorted;
}

//@TODO delete list
void Coliseum::freeColiseum() {
    this->~Coliseum();
}



