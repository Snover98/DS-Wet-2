//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_TRAINER_H
#define HW2_TRAINER_H

#include "splayTree.h"

class Gladiator;
class CompGladsByLevel;

class Trainer{
    private:
    int ID;
    int num_of_gladiators;
    Gladiator& top_gladiator;
    SplayTree<Gladiator, CompGladsByLevel> gladiators;

    public:
    //class functions
    Trainer(int id);
    Trainer();
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

    bool operator<(const Trainer& t);
};

class isInList {
public:
    isInList(int id) : ID(id) {}
    ~isInList();
    bool operator()(Trainer& t) const {
        return t.getID() == ID;
    }

private:
    int ID;
};
#endif //HW2_TRAINER_H
