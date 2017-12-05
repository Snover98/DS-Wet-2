//
// Created by oded on 30/11/17.
//

#include "Trainer.h"
#include "Gladiator.h"

Trainer::Trainer(int id):ID(id), num_of_gladiators(0), top_gladiator(NULL),
                gladiators(SplayTree<Gladiator, CompGladsByLevel>()){}

void Trainer::addGladiator(Gladiator& gladiator) {
    //insert the gladiator and then increase the number of gladiators
    gladiators.insert(gladiator);
    num_of_gladiators++;

    //check if the new gladiator has a higher level than the top gladiator
    if(top_gladiator->getLevel() < gladiator.getLevel()){
        top_gladiator = &gladiator;
    }
}

void Trainer::removeGladiator(Gladiator& g) {
    //if the gladiator was not there
    if(!gladiators.remove(g)){
        return;
    }

    //if g is the trainer's top gladiator, find the new one
    if((*top_gladiator).getID() == g.getID()) {
        top_gladiator = gladiators.findMax();
    }

    //update the number of gladiators
    num_of_gladiators--;

    //delete the gladiator
    delete g;
}

int Trainer::getID() const{
    return this->ID;
}

int Trainer::getNumOfGladiators() const{
    return this->num_of_gladiators;
}

Gladiator* Trainer::getTopGladiator() const{
    return this->top_gladiator;
}

SplayTree<Gladiator, CompGladsByLevel>& Trainer::getGladiators() const{
    return this->gladiators;
};