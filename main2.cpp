//
// Created by oded on 05/12/17.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include "Gladiator.h"
#include "Trainer.h"
#include <iostream>
using namespace std;

bool func(CompGladsByID<Gladiator>& comp) {
    CompGladsByID<Gladiator> comp1;
    comp = comp1;
}

int cTest(CompGladsByID<Gladiator>& comp, Gladiator& g1, Gladiator& g2){
    cout << comp(g1,g2);
}

int main(int argc, const char**argv) {
    Gladiator g1(10);
    Gladiator g2(10);
    CompGladsByID<Gladiator> comp = CompGladsByID<Gladiator>();
    //cTest(comp, g1, g2);
    if(comp(g1,g2)==0) {
        return 1;
    }
    return 0;
}

