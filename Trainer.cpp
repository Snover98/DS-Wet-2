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

    Gladiator gladiator1(gladiatorID);
    Gladiator& gladiator2 = gladiators.find(gladiator1);

    //Do we need to use 'free' or 'delete'? this became quiet confusing..
    delete gladiator2;

    gladiators.remove(gladiator);

    if(topRemoved) {
        Gladiator& topGladiator = gladiators.findTop();
        top_gladiator = topGladiator;
    }
}