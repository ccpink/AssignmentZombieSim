//
// Created by ccpin on 12/11/2020.
//

#include <iostream>
#include <random>
#include <ctime>
#include "Human.h"
#include "Zombie.h"
#include "vector"
#include <windows.h>

using namespace std;
// Game stats
int maxHumans = 50;
int maxZombie = 8;
bool targeted;
const int gridSize = 20;
// Vector Initialization
std::vector<Zombie> ListOfAllZombies;
std::vector<Human> ListOfAllHumans;
std::vector<int> deleteHumanIndex;
std::vector<int> deleteZombieIndex;
vector < pair<int,int> > killedHumans;
vector < pair<int,int> > newZombies;
vector < pair<int,int> > starvedZombies;
// Grid Intialization
int grid[gridSize][gridSize];

// Intitialization of all functions
pair<int, int> getCoordinates(int x, int y, std::string direction);
int numOfZombies();
int numOfHumans();
void removeDeadHumans();
void removeStarvedZombies();
int getRandomNumber();
void InitializeGrid();
void InitializeEntities(int numOfZombies, int numOfHumans);
void getStarvedZombies();
void getRecruitedHumans();
void getTurnedZombies();
void moveAllZombies();
void moveAllHumans();
void printOut();
std::vector<std::string> getOpenSpacesZombie(Zombie zombie);
std::vector<std::string> getOpenSpacesHuman(Human human);



void getTurnedZombies() {
    newZombies.clear();
    killedHumans.clear();
    pair<int,int> aPair;
    string direction;
    int newZombieY = 0;
    int newZombieX = 0;

    for (auto &zombie : ListOfAllZombies) {
        direction = "";
        std::vector<string> openSpaces = getOpenSpacesZombie(zombie);

        if (openSpaces.empty() || !targeted || !zombie.canTurn()) {
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

pair<int, int> getCoordinates(int x, int y, std::string direction)
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

    pair<int,int> aPair;
    aPair.first = newX;
    aPair.second = newY;

    return aPair;
}


void getRecruitedHumans()
{
    string direction;
    int newHumanY = 0;
    int newHumanX = 0;

    for (auto &human : ListOfAllHumans) {
        direction = "";
        std::vector<string> openSpaces = getOpenSpacesHuman(human);

        if (openSpaces.empty() || !human.canRecruit()) {
            continue;
        }

        human.setOpenDirections(openSpaces);
        direction = human.recruitHuman();

        if (direction == "North") {
            newHumanY = human.yPosition + 1;
            newHumanX = human.xPosition;
        } else if (direction == "South") {
            newHumanY = human.yPosition - 1;
            newHumanX = human.xPosition;
        } else if (direction == "East") {
            newHumanY = human.yPosition;
            newHumanX = human.xPosition + 1;
        } else if (direction == "West") {
            newHumanY = human.yPosition;
            newHumanX = human.xPosition - 1;
        };

        //Set the new XY to 1
        grid[newHumanX][newHumanY] = 1;

        //return a vector of pairs?
        ListOfAllHumans.emplace_back(Human(newHumanX, newHumanY));
    }
}

void getStarvedZombies() {
    starvedZombies.clear();
    for (auto &zombie : ListOfAllZombies) {

        //For each zombie check if they are starved
        if (! zombie.isStarved())
            continue;

        //If they are get their current x/y and set it to 1
        grid[zombie.xPosition][zombie.yPosition] = 1;

        //Add the deleted zombies index to the deleted zombie index vector
        pair<int,int> aPair;
        aPair.first = zombie.xPosition;
        aPair.second = zombie.yPosition;
        starvedZombies.emplace_back(aPair);

        //Make it return vector of pairs
        ListOfAllHumans.emplace_back(Human(zombie.xPosition, zombie.yPosition));
    }
}

// Get a random int between 0-gridSize
int getRandomNumber() {
    return rand() % gridSize;
}

// Set the grid to all ones
void InitializeGrid(){
    for (auto &i : grid) {
        for (int &j : i) {
            j = 0; // Null Pointers
        }
    }
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
    // Get the directions the entity can go // Iteration 8 //
    if (canHeadNorth) {
        if (grid[xPos][yPos + 1] == 1) {
            openSpaces.emplace_back("North");
            targeted = true;
        }
    }

    if (canHeadSouth) {
        if (grid[xPos][yPos - 1] == 1) {
            openSpaces.emplace_back("South");
            targeted = true;
        }
    }
    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 1) {
            openSpaces.emplace_back("East");
            targeted = true;
        }
    }
    if (canHeadWest) {
        if (grid[xPos - 1][yPos] == 1) {
            openSpaces.emplace_back("West");
            targeted = true;
        }
    }
    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == 1) {
            openSpaces.emplace_back("North-East");
            targeted = true;
        }
    }
    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == 1) {
            openSpaces.emplace_back("North-West");
            targeted = true;
        }
    }
    if (canHeadSouth && canHeadWest ){
        if (grid[xPos - 1][yPos - 1] == 1) {
            openSpaces.emplace_back("South-West");
            targeted = true;
        }
    }
    if (canHeadSouth && canHeadEast ) {
        if (grid[xPos + 1][yPos - 1] == 1) {
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
            // Reset the hunger when he has targeted
            zombie.resetHunger();
            // set the killed human
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


    //TODO: Edit this to send out ASCII characters
    //TODO: Add Color
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
    int zombiesLeft;
    int humansLeft;
    srand((unsigned) GetTickCount());
    // Entities
    InitializeGrid();
    // Entities on Grid
    InitializeEntities(maxZombie, maxHumans);

    double counter = 0;
    double pauseInterval = 0.9;
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

            // Turn Zombie Check
            getTurnedZombies(); //

            int x;
            int y;
            for (auto &newZombie : newZombies) {
                x = newZombie.first;
                y = newZombie.second;

                ListOfAllZombies.emplace_back(Zombie(x, y));
            }
            // Remove Turned Humans From Human Vector
            removeDeadHumans(); //
            // Recruit Human
            getRecruitedHumans(); //
            // Check If Zombies Are Starved
            getStarvedZombies(); // GENERATES A
            // Remove Starved Zombies
            removeStarvedZombies(); //

            iterationNum++;
            std::cout << "" << endl << endl;
            std::cout << "Current Iteration: " << endl;
            std::cout << iterationNum << endl << endl;
            printOut();

            counter = 0;

            //TODO:: Something is wrong with the creation of zombies and humans during the loop

            zombiesLeft = numOfZombies();
            humansLeft = numOfHumans();
            if (iterationNum == 1000 || zombiesLeft == 0 || humansLeft == 0 )
                break;
        }
    }
}

int numOfZombies(){
    int numberOfZombies = 0;
    for (auto &zombie : ListOfAllZombies) {
        numberOfZombies++;
    }
    return numberOfZombies;
}

int numOfHumans(){
    int numberOfHumans = 0;
    for (auto &human : ListOfAllHumans) {
        numberOfHumans++;
    }
    return numberOfHumans;
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

void removeStarvedZombies() {
    int count = 0;
    int x;
    int y;
    deleteZombieIndex.clear();

    count = 0;
    for (auto &zombie : ListOfAllZombies) {
        for (auto &starvedZombie : starvedZombies) {
            x = starvedZombie.first;
            y = starvedZombie.second;

            if (zombie.getXPosition() == x && zombie.getYPosition() == y) {
                deleteZombieIndex.emplace_back(count);
            }
        }
        count++;
    }

    for (auto &index : deleteZombieIndex) {
        ListOfAllZombies.erase(ListOfAllZombies.begin() + index);
    }
}
