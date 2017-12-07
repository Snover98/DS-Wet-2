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
    List<Trainer>* trainers_list;
    SplayTree<Gladiator>* splay_glads_id;
    SplayTree<Gladiator>* splay_glads_lvl;
    Gladiator* top_gladiator;
    int gladiators_num;

    void emptyLevelTrees();
public:
    //// Constructs a new Coliseum
    Coliseum();
    ~Coliseum();

    void AddTrainerToColiseum(int trainerID);
    void AddGladiatorToColiseum(int gladiatorID, int trainerID, int level);
    void FreeGladiatorFromColiseum(int gladiatorID);
    void LevelUpGladiatorInColiseum(int gladiatorID, int level_increase);
    Gladiator& GetTopGladiator();
    int getTopGladiatorInTrainer(int trainerID);
    void getColiseumGladiatorsByLevel(int trainerID, int **gladiators,
                                      int *num_of_gladiator);
    void UpgradeGladiatorIDInColiseum(int gladiatorID, int upgradedID);
    void UpdateLevelsInColiseum(int stimulant_code, int stimulant_factor);

    void mergeGladiatorsArrays(Gladiator** arr1, int size1,
                                      Gladiator** arr2, int size2,
                                      Gladiator** new_arr);
};



#endif //DS_WET_2_COLISEUM_H
