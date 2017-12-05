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
    List<Trainer>* trainersList;
    SplayTree<Gladiator>& splayGladsId;
    SplayTree<Gladiator>& splayGladsLvl;
    Gladiator* topGladiator;
    int gladiatorsNum;

    void emptyLevelTrees();
public:
    //// Constructs a new Coliseum
    Coliseum();
    ~Coliseum();

    void AddTrainerToColiseum(int trainerID);
    void AddGladiatorToColiseum(int gladiatorID, int trainerID, int level);
    void FreeGladiatorFromColiseum(int gladiatorID);
    void LevelUpGladiatorInColiseum(int gladiatorID, int levelIncrease);
    Gladiator& GetTopGladiator();
    int getTopGladiatorInTrainer(int trainerID);
    int getGladiatorsNum();
    void getColiseumGladiatorsByLevel(int trainerID, int **gladiators,
                                      int *numOfGladiator);
    void UpgradeGladiatorIDInColiseum(int gladiatorID, int upgradedID);
    void UpdateLevelsInColiseum(int stimulantCode, int stimulantFactor);

    void mergeGladiatorsArrays(Gladiator** arr1, int size1,
                                      Gladiator** arr2, int size2,
                                      Gladiator** newArr);
};



#endif //DS_WET_2_COLISEUM_H
