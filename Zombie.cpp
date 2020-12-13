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
Zombie::Zombie(int x, int y, int ID) : Entity(x, y, true, ID) {

}

// Get a direction for the human that is being turned into a zombie
std::string Zombie::turnZombie() {
    std::string direction =  openDirections.at(rand() % openDirections.size());

    if (getCounter() == 8) {
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
    std::string direction =  openDirections.at(rand() % openDirections.size());

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

    incrementCounter();
}

void Zombie::setOpenDirections(std::vector<std::string> directions) {
    openDirections = std::move(directions);
}

