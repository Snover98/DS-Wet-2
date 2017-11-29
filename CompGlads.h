//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#ifndef HW2_COMPGLADS_H
#define HW2_COMPGLADS_H

#include "Gladiator.h"
class Gladiator;

class CompGladsByID{
    public:
    CompGladsByID();
    /*****************COMPARISON************************
     * Compares the the inputted Gladiators by their IDs
     * return values:
     * if the ids are the same, 0
     * if g1.id < g2.id, -1
     * if g1.id > g2.id, 1
     **************************************************/
    virtual int operator()(Gladiator& g1, Gladiator& g2);
    //works the same, just with an id and a gladiator
    virtual int operator()(int id, Gladiator& g);
    virtual int operator()(Gladiator& g, int id);
};

class CompGladsByLevel : public CompGladsByID{
public:
    CompGladsByLevel() = default;
    /*****************COMPARISON************************
     * Compares the the inputted Gladiators by their Levels.
     * If they have the same level, they are compared by id IN REVERSE
     * return values:
     * if g1.level < g2.level, -1
     * if g1.level > g2.level, 1
     * if g1.level == g2.level and g1.id < g2.id, 1
     * if g1.level == g2.level and g1.id > g2.id, -1
     * if g1.level == g2.level and g1.id == g2.id, 0
     **************************************************/
    int operator()(Gladiator& g1, Gladiator& g2) override;
};



#endif //HW2_COMPGLADS_H
