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



Zombie::Zombie(int x, int y, int ID) : Entity(x, y, true, ID) {

}

std::string Zombie::turnZombie() {
    std::shuffle( openDirections.begin(), openDirections.end() , std::mt19937(std::random_device()()));
    std::string direction;

    direction =  openDirections.at(0);

    if (getCounter() == 8){
    if (direction == "North")
    {
        resetCounter();
        return "North";
    }
    else if(direction == "South")
    {
        resetCounter();
        return "South";
    }
    else if (direction == "East")
    {
        resetCounter();
        return "East";
    }
    else if (direction == "West")
    {
        resetCounter();
        return "West";
    }
    else if (direction == "North-West")
    {
        resetCounter();
        return "North-West";
    }
    else if (direction == "South-West")
    {
        resetCounter();
        return "South-West";
    }
    else if (direction == "North-East")
    {
        resetCounter();
        return "North-East";
    }
    else if (direction == "South-East")
    {
        resetCounter();
        return "South-East";

    }

    }

    return "";
}

void Zombie::move(){
    std::shuffle( openDirections.begin(), openDirections.end() , std::mt19937(std::random_device()()));

    std::string direction =  openDirections.at(0);

    if (direction == "North")
    {
        yPosition = yPosition + 1;


    }
    else if(direction == "South")
    {
        yPosition = yPosition - 1 ;


    }
    else if (direction == "East")
    {
        xPosition = xPosition + 1;

    }
    else if (direction == "West")
    {
        xPosition = xPosition - 1;

    }
    else if (direction == "North-West")
    {
        yPosition = yPosition + 1;
        xPosition = xPosition - 1;

    }
    else if (direction == "South-West")
    {
        yPosition = yPosition - 1;
        xPosition = xPosition - 1;

    }
    else if (direction == "North-East")
    {
        yPosition = yPosition + 1;
        xPosition = xPosition + 1;

    }
    else if (direction == "South-East")
    {
        yPosition = yPosition - 1;
        xPosition = xPosition + 1;
    }

    incremementCounter();
}

void Zombie::setOpenDirections(std::vector<std::string> directions) {
    openDirections = std::move(directions);
}

