//
// Created by ccpin on 12/11/2020.
//

#include <iostream>
#include <random>
#include <ctime>
#include "Human.h"
#include "Zombie.h"
#include "vector"
#include "classValues.h"
#include "Entity.h"
#include <windows.h>

using namespace std;

int maxHumans = 2;
int maxZombie = 1;
bool targeted;
const int gridSize = 2;

std::vector<Zombie> ListOfAllZombies;
std::vector<Human> ListOfAllHumans;
std::vector<int> deleteHumanIndex;
vector < pair<int,int> > killedHumans;
int grid[gridSize][gridSize];

//Bias of movement is caused when a choice of move/eat/breed are based on a non-random
// selection of the squares around an organism. Think of a tic tac toe grid with an
// organism in the center. If its routine is always to look around itself starting top
// left (clock-wise), then the bias of movement would be up to the left. To eliminate this.
// Load all the possible valid locations into a vector and then shuffle (randomize) the vector.

//Only one organism in each location of the array (given that it is an array).
//
//Zombies randomly move unless there is a target available
//
//Humans randomly move all the time.

// removal of all the dead human entities
void removeDeadHumans();

// Get a random int between 0-gridSize
int getRandomNumber() {
    srand((unsigned) GetTickCount());
    return rand() % gridSize;
}

// Set the grid to all ones
void InitializeGrid(){
    for (auto &i : grid)
    {
        for (int &j : i)
        {
            j = 0; // Null Pointers
        }
    }
}

// Initialize all the zombie and human entities
void InitializeEntities(int numOfZombies, int numOfHumans){
    int x;
    int y;
    int ID = 0;

    for (int i = 0; i < numOfZombies; i++) {
        while (true) {
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0) {
                ListOfAllZombies.emplace_back(Zombie(x, y, ID));
                grid[x][y] = 2;
                ID++;
                break;
            }
        }
    }

    ID = 0;
    for (int i = 0; i < numOfHumans; i++) {
        while (true) {
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0) {
                ListOfAllHumans.emplace_back(Human(x, y, ID));
                grid[x][y] = 1;
                ID++;
                break;
            }
        }
    }
}

// Get the open spaces for the zombie
std::vector<std::string> getOpenSpacesZombie(Zombie zombie) {
    int xPos = zombie.getXPosition();
    int yPos = zombie.getYPosition();
    targeted = false; // Zombie
    vector<std::string> openSpaces; // Open or targets

    bool canHeadNorth = true;
    bool canHeadSouth = true;
    bool canHeadEast = true;
    bool canHeadWest = true;


    // Get the cardinal directions the entity can go
    if (xPos == gridSize - 1) {
        canHeadEast = false;
    }

    if (xPos == 0) {
        canHeadWest = false;
    }

    if (yPos == gridSize - 1) {
        canHeadNorth = false;
    }

    if (yPos == 0) {
        canHeadSouth = false;
    }

    // Get the directions the entity can go
    if (canHeadNorth) {
        if (grid[xPos][yPos + 1] == 1)
        {
            openSpaces.emplace_back("North");
            targeted = true;
        }
    }

    if (canHeadSouth) {
        if (grid[xPos][yPos - 1] == 1)
        {
            openSpaces.emplace_back("South");
            targeted = true;
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 1)
        {
            openSpaces.emplace_back("East");
            targeted = true;
        }
    }

    if (canHeadWest) {
        if (grid[xPos - 1][yPos] == 1) // West
        {
            openSpaces.emplace_back("West");
            targeted = true;
        }
    }

    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == 1)
        {
            openSpaces.emplace_back("North-East");
            targeted = true;
        }
    }

    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == 1)
        {
            openSpaces.emplace_back("North-West");
            targeted = true;
        }
    }

    if (canHeadSouth && canHeadWest ){
        if (grid[xPos - 1][yPos - 1] == 1) //South-West
        {
            openSpaces.emplace_back("South-West");
            targeted = true;
        }
    }

    if (canHeadSouth && canHeadEast ) {
        if (grid[xPos + 1][yPos - 1] == 1) //South-East
        {
            openSpaces.emplace_back("South-East");
            targeted = true;
        }
    }

    // if there is a target**
    if (targeted) {
        return openSpaces;
    }

    // If There are no humans to eat or targets
    if (canHeadNorth){
        if (grid[xPos][yPos + 1] == 0)
        {
            openSpaces.emplace_back("North");
        }
    }

    if (canHeadSouth){
        if (grid[xPos][yPos - 1] == 0)
        {
            openSpaces.emplace_back("South");
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 0)
        {
            openSpaces.emplace_back("East");
        }
    }

    if (canHeadWest){
        if (grid[xPos - 1][yPos] == 0)
        {
            openSpaces.emplace_back("West");
        }
    }

    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == 0)
        {
            openSpaces.emplace_back("North-West");
        }
    }

    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == 0)
        {
            openSpaces.emplace_back("North-East");
        }
    }

    if (canHeadSouth && canHeadEast) {
        if (grid[xPos + 1][yPos - 1] == 0)
        {
            openSpaces.emplace_back("South-East");
        }
    }

    if (canHeadSouth && canHeadWest) {
        if (grid[xPos - 1][yPos + 1] == 0)
        {
            openSpaces.emplace_back("South-West");
        }
    }
    return openSpaces;
}


// Get the open spaces the Human can go
std::vector<std::string> getOpenSpacesHuman(Human human) {
    int xPos = human.getXPosition();
    int yPos = human.getYPosition();
    vector<std::string> openSpaces; // Open or targets

    bool canHeadNorth = true;
    bool canHeadSouth = true;
    bool canHeadEast = true;
    bool canHeadWest = true;

    // Get the cardinal directions the entity can go
    if (xPos == gridSize - 1) {
        canHeadEast = false;
    }

    if (xPos == 0) {
        canHeadWest = false;
    }

    if (yPos == gridSize - 1) {
        canHeadNorth = false;
    }

    if (yPos == 0) {
        canHeadSouth = false;
    }

    // Get the directions the entity can go
    if (canHeadNorth) {
        if (grid[xPos][yPos + 1] == 0) {
            openSpaces.emplace_back("North");
        }
    }

    if (canHeadSouth) {
        if (grid[xPos][yPos - 1] == 0) {
            openSpaces.emplace_back("South");
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 0) {
            openSpaces.emplace_back("East");
        }
    }

    if (canHeadWest){
        if (grid[xPos - 1][yPos] == 0) {
            openSpaces.emplace_back("West");
        }
    }

    return openSpaces;
}

// Move all the zombie entities
void moveAllZombies() {
    int currXPos;
    int currYPos;

    int newXPos;
    int newYPos;

    for (auto &zombie : ListOfAllZombies) {
        std::vector<string> openSpaces = getOpenSpacesZombie(zombie);

        if (openSpaces.empty()) {
            continue;
        }

        zombie.setOpenDirections(openSpaces);

        currXPos = zombie.xPosition;
        currYPos = zombie.yPosition;
        zombie.move();
        newXPos = zombie.xPosition;
        newYPos = zombie.yPosition;

        grid[currXPos][currYPos] = 0;
        grid[newXPos][newYPos] = 2;

        pair<int,int> aPair;
        aPair.first = newXPos;
        aPair.second = newYPos;

        if (targeted) {
            killedHumans.emplace_back(aPair);
        }
    }
}

// Move all the human entities
void moveAllHumans() {
    for (auto &human : ListOfAllHumans) {
        std::vector<string> openHumanSpaces = getOpenSpacesHuman(human);

        if (openHumanSpaces.empty()) {
            continue;
        }

        human.setOpenDirections(openHumanSpaces);

        int currXPos = human.xPosition;
        int currYPos = human.yPosition;
        human.move();
        int newXPos = human.xPosition;
        int newYPos = human.yPosition;

        grid[currXPos][currYPos] = 0;
        grid[newXPos][newYPos] = 1;
    }
}

//Print out the 2d array
void printOut() {
    int column = 0;

    for (auto &row : grid) {
        for (int &value : row) {
            column++;

            string status = (value == 0) ? "_" : to_string(value);
            cout << status;

            if (column == gridSize) {
                column = 0;
                cout << "" << endl;
            }
        }
    }
}

int main() {
    // Entities
    InitializeGrid();
    // Entities on Grid
    InitializeEntities(maxZombie, maxHumans);

    double counter = 0;
    double pauseInterval = 5;
    clock_t startTime = clock();
    clock_t previousTime = startTime;

    int iterationNum = 1;
    std::cout << "" << endl << endl << endl << endl;
    std::cout << "Current Iteration: " << endl;
    std::cout << iterationNum << endl << endl << endl;
    printOut();

    while(true) {
        startTime = clock();
        counter += startTime - previousTime;
        previousTime = startTime;

        if (counter > (pauseInterval * CLOCKS_PER_SEC)) {
            moveAllZombies();
            removeDeadHumans();
            moveAllHumans();

            iterationNum++;
            std::cout << "" << endl << endl;
            std::cout << "Current Iteration: " << endl;
            std::cout << iterationNum << endl << endl;
            printOut();

            counter = 0;
        }
    }
}
// Remove all the dead humans
// Currently doesn't work :) the zombies end up dying
void removeDeadHumans() {
    int count = 0;
    int x;
    int y;
    deleteHumanIndex.clear();

    count = 0;
    for (auto &human : ListOfAllHumans) {
        for (auto &killedHuman : killedHumans) {
            x = killedHuman.first;
            y = killedHuman.second;

            if (human.getXPosition() == x && human.getYPosition() == y) {
                deleteHumanIndex.emplace_back(count);
            }
        }
        count++;
    }

    for (auto &index : deleteHumanIndex) {
        ListOfAllHumans.erase(ListOfAllHumans.begin() + index);
    }
}
