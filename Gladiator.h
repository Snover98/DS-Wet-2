//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_GLADIATOR_H
class Trainer;

class Gladiator{
private:
    int ID;             //the gladiator's unique ID. is positive
    int level;          //the gladiator's level. is positive
    Trainer* trainer;   //reference to the trainer that owns the gladiator

public:
    //class functions
    Gladiator(int id, int lv, Trainer* t);
    Gladiator(int id, int lv, Trainer& t);
    Gladiator(int id);
    ~Gladiator();

    //getters
    Trainer& getTrainer() const;
    int getID() const;
    int getLevel() const;

    //setters
    void setID(int ID);
    void setLevel(int level);
};








#define HW2_GLADIATOR_H

#endif //HW2_GLADIATOR_H
