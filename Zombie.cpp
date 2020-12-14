//
// Created by ccpin on 12/8/2020.
//

#include<string>
#include <iostream>
#include <utility>
#include <vector>
#include "Zombie.h"
#include <random>
#include <algorithm>    // std::random_shuffle


//Zombie Constructor
Zombie::Zombie(int x, int y) : Entity(x, y) {

}

// Get a direction for the human that is being turned into a zombie
std::string Zombie::turnZombie() {
    std::string direction =  openDirections.at(rand() % openDirections.size());

    if ((getCounter() - 1) == 8) {
        if (direction == "North") {
            resetCounter();
            return "North";
        } else if(direction == "South") {
            resetCounter();
            return "South";
        } else if (direction == "East") {
            resetCounter();
            return "East";
        } else if (direction == "West") {
            resetCounter();
            return "West";
        } else if (direction == "North-West") {
            resetCounter();
            return "North-West";
        } else if (direction == "South-West") {
            resetCounter();
            return "South-West";
        } else if (direction == "North-East") {
            resetCounter();
            return "North-East";
        } else if (direction == "South-East") {
            resetCounter();
            return "South-East";
        }
    }

    return "Your Stupid :)";
}

// Move all zombies
void Zombie::move() {
    std::string direction = openDirections.at(rand() % openDirections.size());

    if (direction == "North") {
        yPosition = yPosition + 1;
    } else if(direction == "South") {
        yPosition = yPosition - 1 ;
    } else if (direction == "East") {
        xPosition = xPosition + 1;
    } else if (direction == "West") {
        xPosition = xPosition - 1;
    } else if (direction == "North-West") {
        yPosition = yPosition + 1;
        xPosition = xPosition - 1;
    } else if (direction == "South-West") {
        yPosition = yPosition - 1;
        xPosition = xPosition - 1;
    } else if (direction == "North-East") {
        yPosition = yPosition + 1;
        xPosition = xPosition + 1;
    } else if (direction == "South-East") {
        yPosition = yPosition - 1;
        xPosition = xPosition + 1;
    }

    incrementHunger();
    incrementCounter();
}

void Zombie::setOpenDirections(std::vector<std::string> directions) {
    openDirections = directions;
}

bool Zombie::isStarved()
{
    return _lastEaten - 1 == 3;
}

void Zombie::resetHunger()
{
    _lastEaten = 0;
}

void Zombie::incrementHunger()
{
    _lastEaten++;
}

int Zombie::getLastEaten() {
    return _lastEaten;
}

bool Zombie::canTurn()
{
    return ((getCounter() - 1) >= 8);
}

void Zombie::setTargeting()
{
    _hasTarget = true;
}

void Zombie::loseTarget()
{
    _hasTarget = false;
}

bool Zombie::hasTarget()
{
    return _hasTarget;
}

Zombie::~Zombie() = default;


