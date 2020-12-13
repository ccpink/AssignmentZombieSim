//
// Created by ccpin on 12/8/2020.
//

#ifndef ZOMBIESVSHUMANS_ENTITY_H
#define ZOMBIESVSHUMANS_ENTITY_H





class Entity {

private:
    int counter = 0;
public:
    Entity(int x, int y);
    void resetCounter();
    int getCounter();
    void incrementCounter();
    virtual void move() = 0;
    int xPosition;
    int yPosition;
    int getXPosition();
    int getYPosition();
    ~Entity();
};


#endif //ZOMBIESVSHUMANS_ENTITY_H
