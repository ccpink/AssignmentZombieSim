//
// Created by ccpin on 12/8/2020.
//

#ifndef ZOMBIESVSHUMANS_ZOMBIE_H
#define ZOMBIESVSHUMANS_ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity {

private:
    std::vector<std::string> openDirections;
    int _lastEaten = 0;
    bool _hasTarget = false;
public:
    Zombie(int x, int y);
    ~Zombie();
    std::string turnZombie();

    void incrementHunger();
    void setTargeting();

    void resetHunger();
    void loseTarget();

    int getLastEaten();

    bool isStarved();
    bool hasTarget();
    bool canTurn();

    void move() override;

    void setOpenDirections(std::vector<std::string> directions);
};

#endif //ZOMBIESVSHUMANS_ZOMBIE_H
