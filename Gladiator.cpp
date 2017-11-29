//
// Created by Assaf-Haik-Barouch on 28/11/2017.
//

#include "Gladiator.h"
#include "Trainer.h"

Gladiator::Gladiator(int id, int lv, const Trainer &t): ID(id), level(lv), trainer(t) {}

int Gladiator::getID() {
    return this->ID;
}

int Gladiator::getLevel() {
    return this->level;
}

const Trainer & Gladiator::getTrainer() {
    return this->trainer;
}

void Gladiator::setID(int ID) {
    this->ID = ID;
}

void Gladiator::setLevel(int level) {
    this->level = level;
}