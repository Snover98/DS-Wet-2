//
// Created by oded on 30/11/17.
//

#include "Coliseum.h"
using namespace DSExceptions;

void* Init(){
    return new Coliseum();
}

StatusType AddTrainer(void *DS, int trainerID) {
    if(!DS || trainerID<1) return INVALID_INPUT;

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
    if(!DS || gladiatorID<1 || trainerID<1 || level<1) return INVALID_INPUT;

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
    if(!DS || gladiatorID<1) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->FreeGladiatorFromColiseum(gladiatorID);
    } catch(GladiatorNotFound& e) {
        return FAILURE;
    }

    return SUCCESS;
}




