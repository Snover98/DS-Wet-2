//
// Created by oded on 30/11/17.
//

#include "Trainer.h"
#include "Gladiator.h"

void Trainer::addGladiator(Gladiator& gladiator) {
    ++num_of_gladiators;

    return gladiators.insert(gladiator);
}

void Trainer::removeGladiator(int gladiatorID) {
    --num_of_gladiators;

    bool topRemoved = (top_gladiator.getID()==gladiatorID);

    gladiators.remove(gladiatorID);

    if(topRemoved) {
        Gladiator& topGladiator = gladiators.findTop();
        top_gladiator = topGladiator;
    }
}