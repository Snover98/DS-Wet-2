//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_GLADIATOR_H

#include "Trainer.h"
class Trainer;

class Gladiator{
    private:
    int ID;             //the gladiator's unique ID. is positive
    int level;          //the gladiator's level. is positive
    const Trainer& trainer;   //reference to the trainer that owns the gladiator

    public:
    //class functions
    Gladiator(int id, int lv, const Trainer &t);
    Gladiator();
    ~Gladiator();

    //getters
    const Trainer& getTrainer();
    int getID();
    int getLevel();

    //setters
    void setID(int ID);
    void setLevel(int level);
};








#define HW2_GLADIATOR_H

#endif //HW2_GLADIATOR_H
