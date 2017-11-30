//
// Created by oded on 30/11/17.
//
#include "Coliseum.h"

StatusType Coliseum::AddTrainerToColiseum(int trainerID) {
    List<Trainer>::Iterator it = trainersList.find(isInList(trainerID));

    if(it != trainersList.end())
        return FAILURE;

    while(it<trainerID){
        it++;
    }

    trainersList.insert(Trainer(trainerID));

    return SUCCESS;
}
