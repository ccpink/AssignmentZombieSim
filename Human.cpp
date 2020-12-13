//
// Created by ccpin on 12/8/2020.
//

#include <iostream>
#include "Human.h"
#include <random>
#include <utility>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
// Human Constructor
Human::Human(int x1, int x2) : Entity(x1, x2) {

}

//Human move function
void Human::move(){
    std::string direction =  openDirections.at(rand() % openDirections.size());

    if (direction == "North") {
        yPosition = yPosition + 1;
    } else if(direction == "South") {
        yPosition = yPosition - 1 ;
    } else if (direction == "East") {
        xPosition = xPosition + 1;
    } else if (direction == "West") {
        xPosition = xPosition - 1;
    }

    incrementCounter();

}
// Set the directions the human can go
void Human::setOpenDirections(std::vector<std::string> directions) {
    openDirections = std::move(directions);
}

// Recruit a human
std::string Human::recruitHuman() {
    std::string direction =  openDirections.at(rand() % openDirections.size());

    if ((getCounter() - 1) == 3) {
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
        }



    }

    return "";
}

bool Human::canRecruit() {
    return ((getCounter() - 1) == 3);
}

Human::~Human() = default;
