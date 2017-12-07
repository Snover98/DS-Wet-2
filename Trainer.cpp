//
// Created by oded on 30/11/17.
//

#include "Trainer.h"
#include "Gladiator.h"

Trainer::Trainer(int id):ID(id), num_of_gladiators(0), top_gladiator(NULL),
                gladiators(NULL){
    CompGladsByLevel<Gladiator>* trainer_comp = new CompGladsByLevel<Gladiator>();
    gladiators = new SplayTree<Gladiator>(trainer_comp);
}

void Trainer::addGladiator(Gladiator& gladiator) {
    //insert the gladiator and then increase the number of gladiators
    gladiators->insert(gladiator);
    num_of_gladiators++;

    //comparer by level
    CompGladsByLevel<Gladiator> comp_lv = CompGladsByLevel<Gladiator>();

    //check if the new gladiator has a higher level than the top gladiator
    if(top_gladiator == NULL || comp_lv(gladiator, *top_gladiator) > 0){
        top_gladiator = &gladiator;
    }
}

void Trainer::removeGladiator(Gladiator& g) {
    //if the gladiator was not there
    if(!(gladiators->remove(g))){
        return;
    }

    //if g is the trainer's top gladiator, find the new one
    if((*top_gladiator).getID() == g.getID()) {
        top_gladiator = gladiators->findMax();
    }

    //update the number of gladiators
    num_of_gladiators--;
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

SplayTree<Gladiator>& Trainer::getGladiators(){
    return *(this->gladiators);
};

void Trainer::emptyTree(){
    gladiators->removeAll();
    num_of_gladiators = 0;
}