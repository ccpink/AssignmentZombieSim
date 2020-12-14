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
Entity::Entity(int x, int y) {
    this->xPosition = x;
    this->yPosition = y;
}

// Is it a zombie really??? No


// Get the x position I never use this :)
int Entity::getXPosition() {
    return xPosition;
}

// Get the y position I never use this :)
int Entity::getYPosition() {
    return yPosition;
}

// Increment the counter :)
void Entity::incrementCounter() {
    counter++;
}

void Entity::setOpenDirections(std::vector<std::string> directions) {
    openDirections = directions;
}

std::string Entity::getRandomDirection()
{
    return ! openDirections.empty() ? openDirections.at(rand() % openDirections.size()) : "";
}

Entity::~Entity() = default;
