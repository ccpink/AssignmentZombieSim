//
// Created by ccpin on 12/11/2020.
//

#include <iostream>
#include <ctime>
#include "Human.h"
#include "Zombie.h"
#include "vector"
#include <windows.h>

using namespace std;

// Game stats
int maxHumans = 5;
int maxZombie = 1;
const int gridSize = 5;

// Status Constants
const int _EMPTY = 0;
const int _HUMAN = 1;
const int _ZOMBIE = 2;

// Vector Initialization
vector<Zombie> ListOfAllZombies;
vector<Human> ListOfAllHumans;
vector <pair<int, int>> killedHumans;
vector <pair<int, int>> newZombies;
vector <pair<int, int>> starvedZombies;

// Grid Initialization
int grid[gridSize][gridSize] = { _EMPTY };

// Initialization of all functions
pair<int, int> getCoordinates(int x, int y, string direction);
void removeDeadHumans();
void removeStarvedZombies();
int getRandomNumber();
void InitializeEntities(int numOfZombies, int numOfHumans);
void getStarvedZombies();
vector<Human> getRecruitedHumans();
void getTurnedZombies();
void moveAllZombies();
void moveAllHumans();
void printOut();
vector<string> getOpenSpacesZombie(Zombie &zombie);
vector<string> getOpenSpacesHuman(Human &human);

void getTurnedZombies()
{
    newZombies.clear();
    killedHumans.clear();

    pair<int,int> aPair;
    string direction;
    int newZombieY = 0;
    int newZombieX = 0;

    for (auto &zombie : ListOfAllZombies) {
        direction = "";
        vector<string> openSpaces = getOpenSpacesZombie(zombie);

        if (openSpaces.empty() || ! zombie.hasTarget() || ! zombie.canTurn()) {
            continue;
        }

        zombie.setOpenDirections(openSpaces);
        direction = zombie.turnZombie();

        // get the coordinates
        aPair = getCoordinates(zombie.xPosition, zombie.yPosition, direction);

        // When they turn they eat a bit so
        zombie.resetHunger();

        // Set the new XY to 2
        grid[newZombieX][newZombieY] = 2;

        // The killed human
        killedHumans.emplace_back(aPair);

        newZombies.emplace_back(aPair);
        //Change it so it returns a vector of pairs
        ListOfAllZombies.emplace_back(Zombie(newZombieX, newZombieY));
    }
}

pair<int, int> getCoordinates(int x, int y, string direction)
{
    int newX = 0;
    int newY = 0;

    if (direction == "North") {
        newY = y + 1;
        newX = x;
    } else if (direction == "South") {
        newY = y - 1;
        newX = x;
    } else if (direction == "East") {
        newY = y;
        newX = x + 1;
    } else if (direction == "West") {
        newY = y;
        newX = x - 1;
    } else if (direction == "North-West") {
        newY = y + 1;
        newX = x - 1;
    } else if (direction == "South-West") {
        newY = y - 1;
        newX = x - 1;
    } else if (direction == "North-East") {
        newY = y + 1;
        newX = x + 1;
    } else if (direction == "South-East") {
        newY = y - 1;
        newX = x + 1;
    }

    return make_pair(newX, newY);
}


vector<Human> getRecruitedHumans()
{
    vector<Human> newHumans;
    string direction;
    int newHumanY = 0;
    int newHumanX = 0;

    for (auto &human : ListOfAllHumans) {
        direction = "";
        vector<string> openSpaces = getOpenSpacesHuman(human);

        if (openSpaces.empty() || ! human.canRecruit()) {
            continue;
        }

        human.setOpenDirections(openSpaces);
        direction = human.recruitHuman();

        pair<int, int> newHuman = getCoordinates(human.xPosition, human.yPosition, direction);

        //Set the new XY to 1
        grid[newHuman.first][newHuman.second] = 1;

        //return a vector of pairs?
        newHumans.emplace_back(Human(newHuman.first, newHuman.second));
    }

    return newHumans;
}

void getStarvedZombies()
{
    starvedZombies.clear();
    for (auto &zombie : ListOfAllZombies) {
        //For each zombie check if they are starved
        cout << "Zombie has not eaten in " << zombie.getLastEaten() << " moves.";
        if (! zombie.isStarved()) {
            continue;
        }

        //If they are, get their current x/y and set it to 1
        grid[zombie.xPosition][zombie.yPosition] = 1;

        //Add the deleted zombies index to the deleted zombie index vector
        starvedZombies.emplace_back(make_pair(zombie.xPosition, zombie.yPosition));

        //Make it return vector of pairs
        ListOfAllHumans.emplace_back(Human(zombie.xPosition, zombie.yPosition));
    }
}

// Get a random int between 0-gridSize
int getRandomNumber()
{
    return rand() % gridSize;
}

// Initialize all the zombie and human entities
void InitializeEntities(int numOfZombies, int numOfHumans)
{
    int x;
    int y;

    for (int i = 0; i < numOfZombies; i++) {
        while (true) {
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0) {
                ListOfAllZombies.emplace_back(Zombie(x, y));
                grid[x][y] = 2;

                break;
            }
        }
    }

    for (int i = 0; i < numOfHumans; i++) {
        while (true) {
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0) {
                ListOfAllHumans.emplace_back(Human(x, y));
                grid[x][y] = 1;
                break;
            }
        }
    }
}

// Get the open spaces for the zombie
vector<string> getOpenSpacesZombie(Zombie &zombie)
{
    int xPos = zombie.getXPosition();
    int yPos = zombie.getYPosition();
    vector<string> openSpaces; // Open or targets

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

    // Get the directions the entity can go // Iteration 8 //
    if (canHeadNorth) {
        if (grid[xPos][yPos + 1] == _HUMAN) {
            openSpaces.emplace_back("North");
            zombie.setTargeting();
        }
    }

    if (canHeadSouth) {
        if (grid[xPos][yPos - 1] == _HUMAN) {
            openSpaces.emplace_back("South");
            zombie.setTargeting();
        }
    }
    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == _HUMAN) {
            openSpaces.emplace_back("East");
            zombie.setTargeting();
        }
    }
    if (canHeadWest) {
        if (grid[xPos - 1][yPos] == _HUMAN) {
            openSpaces.emplace_back("West");
            zombie.setTargeting();
        }
    }
    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == _HUMAN) {
            openSpaces.emplace_back("North-East");
            zombie.setTargeting();
        }
    }
    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == _HUMAN) {
            openSpaces.emplace_back("North-West");
            zombie.setTargeting();
        }
    }
    if (canHeadSouth && canHeadWest ){
        if (grid[xPos - 1][yPos - 1] == _HUMAN) {
            openSpaces.emplace_back("South-West");
            zombie.setTargeting();
        }
    }
    if (canHeadSouth && canHeadEast ) {
        if (grid[xPos + 1][yPos - 1] == _HUMAN) {
            openSpaces.emplace_back("South-East");
            zombie.setTargeting();
        }
    }

    // if there is a target**
    if (zombie.hasTarget()) {
        return openSpaces;
    }

    // If There are no humans to eat or targets
    if (canHeadNorth){
        if (grid[xPos][yPos + 1] == 0) {
            openSpaces.emplace_back("North");
        }
    }
    if (canHeadSouth){
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
    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == 0) {
            openSpaces.emplace_back("North-West");
        }
    }
    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == 0) {
            openSpaces.emplace_back("North-East");
        }
    }
    if (canHeadSouth && canHeadEast) {
        if (grid[xPos + 1][yPos - 1] == 0) {
            openSpaces.emplace_back("South-East");
        }
    }
    if (canHeadSouth && canHeadWest) {
        if (grid[xPos - 1][yPos + 1] == 0) {
            openSpaces.emplace_back("South-West");
        }
    }
    return openSpaces;
}

// Get the open spaces the Human can go
vector<string> getOpenSpacesHuman(Human &human) {
    int xPos = human.getXPosition();
    int yPos = human.getYPosition();
    vector<string> openSpaces; // Open or targets

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
void moveAllZombies()
{
    int currXPos;
    int currYPos;

    for (auto &zombie : ListOfAllZombies) {
        vector<string> openSpaces = getOpenSpacesZombie(zombie);

        if (! openSpaces.empty()) {
            zombie.setOpenDirections(openSpaces);
        }

        currXPos = zombie.xPosition;
        currYPos = zombie.yPosition;
        zombie.move();

        grid[currXPos][currYPos] = 0;
        grid[zombie.xPosition][zombie.yPosition] = 2;

        if (zombie.hasTarget()) {
            // Reset the hunger when he has eaten a human
            zombie.resetHunger();
            zombie.loseTarget();

            // Store the location of the human we need to remove
            killedHumans.emplace_back(make_pair(zombie.xPosition, zombie.yPosition));
        }
    }
}

// Move all the human entities
void moveAllHumans()
{
    for (auto &human : ListOfAllHumans) {
        vector<string> openHumanSpaces = getOpenSpacesHuman(human);

        if (! openHumanSpaces.empty()) {
            human.setOpenDirections(openHumanSpaces);
        }

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
void printOut()
{
    int column = 0;

    for (auto &row : grid) {
        for (int &value : row) {
            column++;

            if (value == _EMPTY) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "_";//char(32);
            } else if (value == _HUMAN) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                cout << char(111);
            } else if (value == _ZOMBIE) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cout << char(90);
            }

            if (column == gridSize) {
                column = 0;
                cout << "" << endl;
            }
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("Zombies: %d, Humans: %d\n", ListOfAllZombies.size(), ListOfAllHumans.size());
}

int main() {
    int zombiesLeft;
    int humansLeft;
    srand((unsigned) GetTickCount());
    // Entities on Grid
    InitializeEntities(maxZombie, maxHumans);

    double counter = 0;
    double pauseInterval = 0.9;
    clock_t startTime = clock();
    clock_t previousTime = startTime;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int iterationNum = 1;
    cout << "" << endl << endl << endl << endl;
    cout << "Current Iteration: " << endl;
    cout << iterationNum << endl << endl << endl;
    printOut();

    while(true) {
        startTime = clock();
        counter += startTime - previousTime;
        previousTime = startTime;

        if (counter > (pauseInterval * CLOCKS_PER_SEC)) {
            moveAllZombies();
            removeDeadHumans();
            moveAllHumans();

            // Turn Zombie Check
//            getTurnedZombies();
//
//            int x;
//            int y;
//            for (auto &newZombie : newZombies) {
//                x = newZombie.first;
//                y = newZombie.second;
//
//                ListOfAllZombies.emplace_back(Zombie(x, y));
//            }
//
//            // Remove Turned Humans From Human Vector
//            removeDeadHumans();
//            // Recruit Human
//            vector<Human> newHumans = getRecruitedHumans();
//            for (auto human : newHumans) {
//                ListOfAllHumans.emplace_back(move(human));
//            }
//            // Check If Zombies Are Starved
            getStarvedZombies();
            removeStarvedZombies();

            iterationNum++;
            cout << "" << endl << endl;
            cout << "Current Iteration: " << endl;
            cout << iterationNum << endl << endl;
            printOut();

            counter = 0;

            //TODO:: Something is wrong with the creation of zombies and humans during the loop

            zombiesLeft = ListOfAllZombies.size();
            humansLeft = ListOfAllHumans.size();

            if (iterationNum == 1000 || zombiesLeft == 0 || humansLeft == 0) {
                cout << "Game Over..." << endl;
                break;
            }
        }
    }
}

// Remove all the dead humans
// Currently doesn't work :) the zombies end up dying
void removeDeadHumans()
{
    vector<int> deadHumanIndices;
    int index = 0;
    int x;
    int y;

    for (auto &human : ListOfAllHumans) {
        for (auto &killedHuman : killedHumans) {
            x = killedHuman.first;
            y = killedHuman.second;

            if (human.getXPosition() == x && human.getYPosition() == y) {
                ListOfAllHumans.erase(ListOfAllHumans.begin() + index);
            }
        }
        index++;
    }
}

void removeStarvedZombies()
{
    vector<int> starvedZombieIndices;
    int index = 0;
    int x;
    int y;

    for (auto &zombie : ListOfAllZombies) {
        for (auto &starvedZombie : starvedZombies) {
            x = starvedZombie.first;
            y = starvedZombie.second;

            if (zombie.getXPosition() == x && zombie.getYPosition() == y) {
                ListOfAllZombies.erase(ListOfAllZombies.begin() + index);
            }
        }
        index++;
    }
}
