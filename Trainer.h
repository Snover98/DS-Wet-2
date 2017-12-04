//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_TRAINER_H
#define HW2_TRAINER_H

#include <clocale>
#include "splayTree.h"

class Gladiator;
class CompGladsByLevel;

class Trainer{
    private:
    int ID;
    int num_of_gladiators;
    Gladiator* top_gladiator;
    SplayTree<Gladiator, CompGladsByLevel> gladiators;

    public:
    //class functions
    Trainer(int id);
    Trainer();
    ~Trainer();

    //getters
    int getID() const;
    int getNumOfGladiators() const;
    Gladiator* getTopGladiator() const;
    SplayTree<Gladiator, CompGladsByLevel>& getGladiators() const;

    //other functions
    //addGladiator
    void addGladiator(Gladiator& gladiator);
    //removeGladiator
    void removeGladiator(Gladiator& g);
    //emptyTree

};


#endif //HW2_TRAINER_H
