//
// Created by oded on 30/11/17.
//

#include "Coliseum.h"

void* Init(){
    return new Coliseum();
}

StatusType AddTrainer(void *DS, int trainerID) {
    if(!DS || trainerID<1) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    StatusType status = coliseum->AddTrainerToColiseum(trainerID);

    return SUCCESS;
}
