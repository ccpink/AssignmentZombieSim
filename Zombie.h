//
// Created by ccpin on 12/8/2020.
//

#ifndef ZOMBIESVSHUMANS_ZOMBIE_H
#define ZOMBIESVSHUMANS_ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity {

private:
    std::vector<std::string> openDirections;
    int lastEaten;
public:
    Zombie(int x, int y);
    ~Zombie();
    std::string turnZombie();

    void incrementHunger();

    void resetHunger();

    bool isStarved();
    bool canTurn();

    void move() override;

    void setOpenDirections(std::vector<std::string> directions);
};

#endif //ZOMBIESVSHUMANS_ZOMBIE_H
