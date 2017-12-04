//
// Created by oded on 30/11/17.
//
#include "Coliseum.h"
using namespace DSExceptions;

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
    Gladiator* glad = &(splayGladsId.find(dummy));

    //if no gladiator was found
    if(glad == NULL){
        throw GladiatorNotFound();
    }

    //check the gladiator's trainer
    Trainer& trainer = (*glad).getTrainer();

    //remove the gladiator from his trainer's tree
    trainer.removeGladiator(*glad);

    //if the gladiator we are removing is the top gladiator
    if(CompGladsByLevel::operator()(topGladiator, *glad) == 0) {
        List<Trainer>::Iterator it = trainersList.begin();
        topGladiator = (*it).getTopGladiator();

        while(it != trainersList.end()){
            if(topGladiator == NULL || (*it).getTopGladiator().getLevel() > topGladiator.getLevel()) {
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
    Gladiator& gladiator = splayGladsId.find(gladiatorID);

    if(!gladiator)
        throw GladiatorNotFound();

    splayGladsLvl.remove(gladiatorID);

    gladiator.getTrainer().getGladiators().remove(gladiatorID);

    gladiator.setLevel(gladiator.getLevel()+levelIncrease);

    splayGladsLvl.insert(gladiator);

    gladiator.getTrainer().getGladiators().insert(gladiator);
}

Gladiator& Coliseum::GetTopGladiator() {
    return topGladiator;
}

int Coliseum::getGladiatorsNum() {
    return gladiatorsNum;
}

int Coliseum::FindTopGladiatorInTrainer(int trainerID) {
    List<Trainer>::Iterator it = trainersList.begin();

    while(it != trainersList.end()){
        if((*it).getID()==trainerID) {
            if((*it).getNumOfGladiators() == 0) {
                return -1;
            } else {
                return (*it).getTopGladiator().getID();
            }
        }
    }

    throw TrainerNotFound();
}

void Coliseum::getColiseumGladiatorsByLevel(int trainerID, int **gladiators,
                                            int *numOfGladiator) {
    if(trainerID < 0) {
        *numOfGladiator = getGladiatorsNum();
        *gladiators = (int*)malloc(sizeof(int)*(*numOfGladiator));
        splayGladsLvl.getByOrder(**gladiators, *numOfGladiator);
    } else {
        List<Trainer>::Iterator it = trainersList.begin();

        while(it != trainersList.end()){
            if((*it).getID()==trainerID) {
                if((*it).getNumOfGladiators() == 0) {
                    *numOfGladiator = 0;
                    *gladiators = NULL;
                    return;
                } else {
                    *numOfGladiator = (*it).getNumOfGladiators();
                    *gladiators = (int*)malloc(sizeof(int)*(*numOfGladiator));
                    (*it).getGladiators().getByOrder(**gladiators, *numOfGladiator);
                    return;
                }
            }
        }

        throw TrainerNotFound();
    }
}

void Coliseum::UpgradeGladiatorIDInColiseum(int gladiatorID, int upgradedID) {
    if(splayGladsId.find(upgradedID))
        throw GladiatorUpgradedIDAlreadyExist();

    Gladiator& gladiator = splayGladsId.find(gladiatorID);

    if(!gladiator)
        throw GladiatorNotFound();

    splayGladsLvl.remove(gladiatorID);
    splayGladsId.remove(gladiatorID);
    gladiator.getTrainer().removeGladiator(gladiatorID);

    gladiator.setID(upgradedID);

    splayGladsId.insert(gladiator);
    splayGladsLvl.insert(gladiator);
    gladiator.getTrainer().addGladiator(gladiator);
}

class stimulatePredicate{
private:
    int stimulateCode;
    int stimulateFactor;
public:
    stimulatePredicate(int stimulateCode, int stimulateFactor):
            stimulateCode(stimulateCode), stimulateFactor(stimulateFactor) {}
    bool operator()(Gladiator& g1) {
        if(g1.getID()%stimulateCode == 0) {
            g1.setLevel(g1.getLevel()*stimulateFactor);
            return true;
        } else {
            return false;
        }
    }
};

void Coliseum::mergeGladiatorsArrays(Gladiator* arr1, int size1,
                              Gladiator* arr2, int size2, Gladiator* newArr) {
    int arr1Counter = 0;
    int arr2Counter = 0;
    int i;
    for(i=0; i<(size1+size2);i++) {
        if(arr1Counter == (size1-1) || arr2Counter == (size2-1))
            break;

        if(arr1[arr1Counter].getLevel() > arr2[arr2Counter].getLevel()) {
            newArr[i] = arr1[arr1Counter];
            arr1Counter++;
        } else if(arr1[arr1Counter].getLevel() < arr2[arr2Counter].getLevel()) {
            newArr[i] = arr2[arr2Counter];
            arr2Counter++;
        } else if(arr1[arr1Counter].getLevel() == arr2[arr2Counter].getLevel()) {
            if(arr1[arr1Counter].getID() < arr2[arr2Counter].getID()) {
                newArr[i] = arr1[arr1Counter];
                arr1Counter++;
            } else {
                newArr[i] = arr2[arr2Counter];
                arr2Counter++;
            }
        }
    }

    while((arr1Counter != (size1-1)) || (arr2Counter != (size2-1))) {
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

void Coliseum::stimulateColiseumTree(SplayTree& tree, int stimulantCode,
                                     int stimulantFactor, int nodesNum) {
    Gladiator* gladsToChange = (Gladiator*)malloc(sizeof(Gladiator*)*nodesNum);
    Gladiator* gladsUnChanged = (Gladiator*)malloc(sizeof(Gladiator*)*nodesNum);
    int *sameNum;
    int *changeNum;
    *sameNum = 0;
    *changeNum = 0;

    tree.getByPredicate(gladsToChange, gladsUnChanged,
        sameNum, changeNum, stimulatePredicate(stimulantCode, stimulantFactor));

    Gladiator* newGlads = (Gladiator*)malloc(sizeof(Gladiator*)*nodesNum);

    mergeGladiatorsArrays(gladsToChange,*changeNum,gladsUnChanged,*changeNum,
                          newGlads);
    free(gladsToChange);
    free(gladsUnChanged);

    tree.removeAll();

    for(int i = 0; i < nodesNum; i++) {
        tree.insert(newGlads[i]);
    }

    free(newGlads);
}

void Coliseum::UpdateLevelsInColiseum(int stimulantCode, int stimulantFactor) {
    stimulateColiseumTree(splayGladsLvl,stimulantCode,
                          stimulantFactor,gladiatorsNum);

    List<Trainer>::Iterator it = trainersList.begin();

    while(it != trainersList.end()){
        stimulateColiseumTree((*it).getGladiators(),stimulantCode,
                              stimulantFactor,(*it).getNumOfGladiators());
    }
}

void Coliseum::freeColiseum() {
    splayGladsLvl.removeAllAndDeleteInfo();
    splayGladsId.removeAll();

    List<Trainer>::Iterator it = trainersList.begin();

    while(it != trainersList.end()){
        (*it).getGladiators().removeAll();
    }
}



