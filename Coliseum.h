//
// Created by oded on 30/11/17.
//

#ifndef DS_WET_2_COLISEUM_H
#define DS_WET_2_COLISEUM_H

#include "linkedList.h"
#include "Gladiator.h"
#include "Trainer.h"
#include "splayTree.h"
#include "library1.h"
#include "CompGlads.h"

class Coliseum{
private:
    List<Trainer> trainersList;
    SplayTree<Gladiator,CompGladsByID> splayGladsId;
    SplayTree<Gladiator,CompGladsByLevel> splayGladsLvl;
    Gladiator& topGladiator;
    int gladiatorsNum;
public:
    //// Constructs a new Coliseum
    Coliseum(): trainersList(), splayGladsId(), splayGladsLvl(),
                topGladiator(), gladiatorsNum(0) {}
    ~Coliseum();

    StatusType AddTrainerToColiseum(int trainerID);
};



#endif //DS_WET_2_COLISEUM_H
