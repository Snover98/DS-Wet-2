//
// Created by oded on 30/11/17.
//

#include "Coliseum.h"
using namespace DSExceptions;

void* Init(){
    void* DS;

    try {
        DS = new Coliseum();
    } catch(std::bad_alloc& e) {
        DS = NULL;
    }

    return DS;
}

StatusType AddTrainer(void *DS, int trainerID) {
    if(DS == NULL || trainerID <= 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->AddTrainerToColiseum(trainerID);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(TrainerAlreadyIn& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType BuyGladiator(void *DS, int gladiatorID, int trainerID, int level) {
    if(DS == NULL || gladiatorID <= 0 || trainerID <= 0 || level <= 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->AddGladiatorToColiseum(gladiatorID, trainerID, level);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(GladiatorAlreadyIn& e) {
        return FAILURE;
    } catch(TrainerNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType FreeGladiator(void *DS, int gladiatorID) {
    if(DS == NULL || gladiatorID <= 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->FreeGladiatorFromColiseum(gladiatorID);
    } catch(GladiatorNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType LevelUp(void *DS, int gladiatorID, int levelIncrease) {
    if(DS == NULL || gladiatorID <= 0 || levelIncrease <= 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->LevelUpGladiatorInColiseum(gladiatorID, levelIncrease);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(GladiatorNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetTopGladiator(void *DS, int trainerID, int *gladiatorID) {
    if(DS == NULL || gladiatorID == NULL || trainerID==0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    if(trainerID<0) {
        *gladiatorID = coliseum->GetTopGladiator().getID();
        return SUCCESS;
    }

    try {
        *gladiatorID = coliseum->getTopGladiatorInTrainer(trainerID);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(TrainerNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType GetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators,
                                   int *numOfGladiator) {
    if(DS == NULL || gladiators == NULL || numOfGladiator == NULL || trainerID == 0)
        return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->getColiseumGladiatorsByLevel(trainerID, gladiators, numOfGladiator);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(TrainerNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType UpgradeGladiator(void *DS, int gladiatorID, int upgradedID) {
    if(DS == NULL || gladiatorID <= 0 || upgradedID <= 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->UpgradeGladiatorIDInColiseum(gladiatorID, upgradedID);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(GladiatorNotFound& e) {
        return FAILURE;
    } catch(GladiatorUpgradedIDAlreadyExist& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType UpdateLevels(void *DS, int stimulantCode, int stimulantFactor) {
    if(DS == NULL || stimulantCode < 1 || stimulantFactor < 1) return INVALID_INPUT;

    if(stimulantFactor == 1) return SUCCESS;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->UpdateLevelsInColiseum(stimulantCode, stimulantFactor);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

void Quit(void** DS) {
    if(DS == NULL || *DS == NULL) return;

    Coliseum* coliseum = static_cast<Coliseum*>(*DS);

    delete coliseum;
}


