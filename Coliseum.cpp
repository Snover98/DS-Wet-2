//
// Created by oded on 30/11/17.
//
#include "Coliseum.h"
using namespace DSExceptions;

void Coliseum::AddTrainerToColiseum(int trainerID) {
    List<Trainer>::Iterator it = trainersList.begin();

    while((*it).getID()<trainerID){
        it++;
    }

    if((*it).getID()==trainerID)
        throw TrainerAlreadyIn();

    trainersList.insert(Trainer(trainerID));
}

void Coliseum::AddGladiatorToColiseum(int gladiatorID, int trainerID, int level) {
    if(splayGladsId.find(gladiatorID))
        throw GladiatorAlreadyIn();

    List<Trainer>::Iterator it = trainersList.begin();

    while((*it).getID()<trainerID){
        it++;
    }

    if(it==trainersList.end())
        throw TrainerNotFound();

    List<Trainer>::Iterator p = it;

    Gladiator* new_gladiator = new Gladiator(gladiatorID,level,*(it));

    //SplayTree& g = (*p).addGladiator(gladiatorID, level,(*p));
    (*p).addGladiator(*new_gladiator);

    if(level>topGladiator.getLevel())
        topGladiator = *new_gladiator;

    if(level>(*p).getTopGladiator().getLevel())
        (*p).getTopGladiator() = *new_gladiator;

    splayGladsId.insert(*new_gladiator);
    splayGladsLvl.insert(*new_gladiator);

    ++gladiatorsNum;
}

void Coliseum::FreeGladiatorFromColiseum(int gladiatorID) {
    Gladiator& twin = splayGladsId.find(gladiatorID);

    if(!twin)
        throw GladiatorNotFound();

    Trainer& trainer = (*twin).getTrainer();
    int gladiatorLvl = (*twin).getLevel();

    splayGladsLvl.remove(gladiatorLvl);

    trainer.removeGladiator(gladiatorID);

    if(!topGladiator) {
        List<Trainer>::Iterator it = trainersList.begin();
        int maxLvl = 0;

        while(it == trainersList.end()){
            if((*it).getTopGladiator().getLevel()>maxLvl) {
                maxLvl = (*it).getTopGladiator().getLevel();
                topGladiator = (*it).getTopGladiator();
            }
            it++;
        }
    }
}
