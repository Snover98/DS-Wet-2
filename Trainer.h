//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_TRAINER_H
#define HW2_TRAINER_H

#include "splayTree.h"
#include "Gladiator.h"
#include "CompGlads.h"

class Gladiator;

class Trainer{
    private:
    int ID;
    int num_of_gladiators;
    Gladiator& top_gladiator;
    SplayTree<Gladiator, CompGladsByLevel> gladiators;

    public:
    //class functions
    Trainer(int id);
    Trainer() = delete;
    ~Trainer();

    //getters
    int getID();
    int getNumOfGladiators();
    Gladiator& getTopGladiator();
    SplayTree<Gladiator, CompGladsByLevel>& getGladiators();

    //setters
    void setID(int ID);

    //other functions
    //addGladiator
    //removeGladiator
    //emptyTree


};





#endif //HW2_TRAINER_H
