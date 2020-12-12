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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int compGuess = rand() % 20 +1;
int numOfH = 1;
int numOfZ = 1;
bool targeted;
const int gridSize = 5;

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

void removeDeadHumans();

// Get a random int between 0-gridSize
int getRandomNumber() {
    int nextRandomInt;

    while (true) {
        srand((unsigned) time(0));
        nextRandomInt = (rand() % gridSize) + 0;

        if (nextRandomInt >= 0 && nextRandomInt < gridSize) {
            break;
        }
    }
    return nextRandomInt;
}

// Set the grid to all ones
void InitializeGrid(){
    for (auto & i : grid)
    {
        for (int & j : i)
        {
            j = 0; // Null Pointers
        }
    }
}

// Get the value at a point on the grid


void setGridPointZombie(int x, int y){
    grid[x][y] = 2;  // Change to a pointer to a zombie //
}

void setGridPointHuman(int x, int y){
    grid[x][y] = 1; // Change to a pointer of a human //
}




void InitializeEntities(int numOfZombies, int numOfHumans){
    int x;
    int y;
    int count = 0;
    int ID = 0;



    for (int i = 0; i < numOfZombies; i++)
    {
        while (true){
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0){
                ListOfAllZombies.emplace_back(Zombie(x,y,ID));


                count +=1;
                ID +=1;
                break;
            }
        }
    } // what

    count = 0;
    for (int i = 0; i < numOfHumans; i++)
    {

        while (true){
            x = getRandomNumber();
            y = getRandomNumber();

            if (grid[x][y] == 0){
                ListOfAllHumans.emplace_back(Human(x,y,ID));

                count +=1;
                ID +=1;
                break;
            }
        }
    }
}


std::vector<std::string> getOpenSpacesZombie(Zombie zombie) {
    int xPos = zombie.getXPosition();
    int yPos = zombie.getYPosition();
    targeted = false; // Zombie
    vector<std::string> openSpaces; // Open or targets

    bool canHeadNorth = true;
    bool canHeadSouth = true;
    bool canHeadEast = true;
    bool canHeadWest = true;

    if (xPos == gridSize - 1){
        canHeadEast = false;
    }
    if (xPos == 0) {
        canHeadWest = false;
    }

    if (yPos == gridSize - 1){
        canHeadNorth = false;
    }

    if (yPos == 0) {
        canHeadSouth = false;
    }


    // If Zombie

    if (canHeadNorth) {
        if (grid[xPos][yPos + 1] == 1)// North
        {
            openSpaces.emplace_back("North");
            targeted = true;
        }
    }
    if (canHeadSouth) {
        if (grid[xPos][yPos - 1] == 1) // South
        {
            openSpaces.emplace_back("South");
            targeted = true;
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 1) // East
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
    if (targeted){
        return openSpaces;
    }

    // If There are no humans to eat or targets
    if (canHeadNorth){
        if (grid[xPos][yPos + 1] == 0)// North
        {
            openSpaces.emplace_back("North");
        }
    }

    if (canHeadSouth){
        if (grid[xPos][yPos - 1] == 0) // South
        {
            openSpaces.emplace_back("South");
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 0) // East
        {
            openSpaces.emplace_back("East");
        }
    }

    if (canHeadWest){
        if (grid[xPos - 1][yPos] == 0) // West // == NULLPOINTER
        {
            openSpaces.emplace_back("West");
        }
    }

    if (canHeadNorth && canHeadWest){
        if (grid[xPos - 1][yPos + 1] == 0) //North-West
        {
            openSpaces.emplace_back("North-West");
        }
    }

    if (canHeadNorth && canHeadEast) {
        if (grid[xPos + 1][yPos + 1] == 0) //North-East
        {
            openSpaces.emplace_back("North-East");
        }
    }

    if (canHeadSouth && canHeadEast) {
        if (grid[xPos + 1][yPos - 1] == 0) //South-West
        {
            openSpaces.emplace_back("South-East");
        }
    }

    if (canHeadSouth && canHeadWest) {
        if (grid[xPos - 1][yPos + 1] == 0) //North-East
        {
            openSpaces.emplace_back("South-West");
        }
    }
    return openSpaces;
}



std::vector<std::string> getOpenSpacesHuman(Human human){
    int xPos = human.getXPosition();
    int yPos = human.getYPosition();
    targeted = false; // Zombie
    vector<std::string> openSpaces; // Open or targets

    bool canHeadNorth = true;
    bool canHeadSouth = true;
    bool canHeadEast = true;
    bool canHeadWest = true;

    if (xPos == gridSize - 1){
        canHeadEast = false;
    }
    if (xPos == 0) {
        canHeadWest = false;
    }

    if (yPos == gridSize - 1){
        canHeadNorth = false;
    }

    if (yPos == 0) {
        canHeadSouth = false;
    }

    if (canHeadNorth){
        if (grid[xPos][yPos + 1] == 0)// North
        {
            openSpaces.emplace_back("North");
        }
    }

    if (canHeadSouth){
        if (grid[xPos][yPos - 1] == 0) // South
        {
            openSpaces.emplace_back("South");
        }
    }

    if (canHeadEast) {
        if (grid[xPos + 1][yPos] == 0) // East
        {
            openSpaces.emplace_back("East");
        }
    }

    if (canHeadWest){
        if (grid[xPos - 1][yPos] == 0) // West // == NULLPOINTER
        {
            openSpaces.emplace_back("West");
        }
    }
    return openSpaces;
}

void moveAllZombies() {
    int currXPos;
    int currYPos;

    int newXPos;
    int newYPos;

    for (auto zom : ListOfAllZombies) {
        std::vector<string> openSpaces = getOpenSpacesZombie(zom);
        if (openSpaces.empty()) {
            continue;
        }

        zom.setOpenDirections(openSpaces);

         currXPos = zom.xPosition;
         currYPos = zom.yPosition;
         zom.move();
         newXPos = zom.xPosition;
         newYPos = zom.yPosition;

        //setGridPointEmpty(currXPos, currYPos);
        grid[currXPos][currYPos] = 0;

        grid[newXPos][newYPos] = 2;
        //setGridPointZombie(newYPos, newXPos);s

        if (targeted) {
            // create a lkist of killed humans
            killedHumans.emplace_back(newXPos,newYPos);
        }
    }
}

void moveAllHumans() {
    for (auto hum : ListOfAllHumans) {
        std::vector<string> checkIfEmpty = getOpenSpacesHuman(hum);
        if (!checkIfEmpty.empty()) {
            hum.setOpenDirections(getOpenSpacesHuman(hum));

            int currXPos = hum.xPosition;
            int currYPos = hum.yPosition;
            hum.move();
            int newXPos = hum.xPosition;
            int newYPos = hum.yPosition;

            //setGridPointEmpty(currXPos, currYPos);
            grid[currXPos][currYPos] = 0;
            //setGridPointHuman(newYPos, newXPos);
            grid[newXPos][newYPos] = 1;
        }
    }
}

void printOut() {
    int column = 0;

    for (auto & row : grid) {
        for (int & value : row) {
            column += 1;
            std::cout << value;

            if (column == gridSize) {
                column = 0;
                std::cout << "" << endl;
            }
        }
    }
}

int main() {
    // Entities
    InitializeGrid();
    // Entities on Grid
    InitializeEntities(numOfZ,numOfH);

    double counter = 0;
    double pauseInterval = 5;
    clock_t startTime = clock();
    clock_t previousTime = startTime;

    for (auto human : ListOfAllHumans) {
        setGridPointHuman(human.xPosition,human.yPosition);
    }

    for (auto zombie : ListOfAllZombies) {
        setGridPointZombie(zombie.xPosition,zombie.yPosition);
    }

    int iterationNum = 1;
    std::cout << "" << endl << endl << endl << endl;
    std::cout << "Current Iteration: " << endl;
    std::cout << iterationNum << endl << endl << endl;
    printOut();

    while(true) {
        startTime = clock();
        counter += startTime - previousTime;
        previousTime = startTime;

        if (counter>pauseInterval * CLOCKS_PER_SEC) {
            moveAllZombies();
            removeDeadHumans();
            moveAllHumans();

            iterationNum +=1;
            std::cout << "" << endl << endl;
            std::cout << "Current Iteration: " << endl;
            std::cout << iterationNum << endl << endl;
            printOut();

            counter = 0;
        }
    }
}

void removeDeadHumans() {
    int count = 0;
    int x;
    int y;
    deleteHumanIndex.clear();

    count = 0;
    for (auto human : ListOfAllHumans) {
        for (const auto & killedHuman : killedHumans) {
            x = killedHuman.first;
            y = killedHuman.second;

            if (human.getXPosition() == x && human.getYPosition() == y) {
                deleteHumanIndex.push_back(count);
            }
        }
        count++;
    }

    for (auto index : deleteHumanIndex) {
        ListOfAllHumans.erase(ListOfAllHumans.begin()+ index);
    }
}

#pragma clang diagnostic pop
