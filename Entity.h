//
// Created by ccpin on 12/8/2020.
//

#ifndef ZOMBIESVSHUMANS_ENTITY_H
#define ZOMBIESVSHUMANS_ENTITY_H





class Entity {

private:
    bool isZombie;
    int counter;
public:
    Entity(int x, int y, bool isZombie, int id);
    void resetCounter();
    int getCounter();
    void incrementCounter();
    bool getIsZombie();
    int xPosition;
    int yPosition;
    int id;
    int getXPosition();
    int getYPosition();
    void setXPosition(int x);
    void setYPosition(int y);
};


#endif //ZOMBIESVSHUMANS_ENTITY_H
