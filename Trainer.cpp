//
// Created by oded on 30/11/17.
//

#include "Trainer.h"

SplayTree& Trainer::addGladiator(int gladiatorID, int level, const Trainer& t) {
    ++num_of_gladiators;

    return gladiators.insert(Gladiator(gladiatorID,level,t));
}

void Trainer::removeGladiator(int gladiatorID) {
    --num_of_gladiators;

    gladiators.remove(Gladiator(gladiatorID));

    if(!top_gladiator) {
        SplayTree& topGladiator = gladiators.getTop();
        top_gladiator = (*topGladiator);
    }
}