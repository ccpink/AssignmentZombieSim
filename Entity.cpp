//
// Created by ccpin on 12/8/2020.
//

#include "Entity.h"

// Set the counter to 0
void Entity::resetCounter() {
    counter = 0;
}

// Get the counter
int Entity::getCounter() {
    return counter;
}

// Entity Constructor
Entity::Entity(int x, int y, bool isZombie, int ID) {
    this->xPosition = x;
    this->yPosition = y;
    this->isZombie = isZombie;
    this->id = ID;
}

// Is it a zombie really??? No
bool Entity::getIsZombie() {
    return isZombie;
}

// Get the x position I never use this :)
int Entity::getXPosition() {
    return xPosition;
}

// Get the y position I never use this :)
int Entity::getYPosition() {
    return yPosition;
}

// Set the y position I never use this :)
void Entity::setYPosition(int y) {
    yPosition = y;
}

// Set the x position I never use this :)
void Entity::setXPosition(int x) {
    xPosition = x;
}

// Increment the counter :)
void Entity::incrementCounter() {
    counter++;
}
