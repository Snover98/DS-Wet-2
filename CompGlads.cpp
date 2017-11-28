//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#include "CompGlads.h"
#include "Gladiator.h"

/*****************************************
* Compares the the inputted id and the gladiator's id
* return values:
* if the ids are the same, 0
* if id < g.id, -1
* if id > g.id, 1
*******************************************/
virtual int operator()(int id, Gladiator& g){
    if(id == g.getID()){
        return 0;
    }

    return (id < g.getID())? -1: 1;
}

/*****************************************
* Compares the the inputted id and the gladiator's id
* return values:
* if the ids are the same, 0
* if id < g.id, 1
* if id > g.id, -1
*******************************************/
virtual int operator()(Gladiator& g, int id){
    return (-1)*CompGladsByID::operator()(id,g);
}


/*****************************************
* Compares the the inputted Gladiators by their IDs
* return values:
* if the ids are the same, 0
* if g1.id < g2.id, -1
* if g1.id > g2.id, 1
*******************************************/
int CompGladsByID::operator()(Gladiator& g1, Gladiator& g2) {
    return CompGladsByID::operator()(g1.getID(), g2);
}

/*****************************************
* Compares the the inputted Gladiators by their Levels.
* If they have the same level, they are compared by id IN REVERSE
* return values:
* if g1.level < g2.level, -1
* if g1.level > g2.level, 1
* if g1.level == g2.level and g1.id < g2.id, 1
* if g1.level == g2.level and g1.id > g2.id, -1
* if g1.level == g2.level and g1.id == g2.id, 0
**************************************************/
int CompGladsByLevel::operator()(Gladiator &g1, Gladiator& g2) {
    if(g1.getLevel() == g2.getLevel()){
        return (-1)*CompGladsByID::operator()(g1, g2);
    }

    return (g1.getLevel() < g2.getLevel())? -1: 1;
}