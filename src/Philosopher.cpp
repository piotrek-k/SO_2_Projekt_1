#include "Philosopher.h"
#include <thread>
#include <chrono> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <exception>
#include <curses.h>

void Philosopher::AssignFork(Fork* fork){
    this->availableForks.push_back(fork);
}

void Philosopher::SimulateLife(){
    if(this->availableForks.size() != 2){
        throw "Brak wystarczajacej liczby widelcow";
    }

    this->keepAlive = true;
    srand (time(NULL));
    float randomNum = (rand() % 10)/10;
    int actionLength = (2+randomNum) * 1000;
    auto forkPickupRetryTime = std::chrono::milliseconds(100);

    while(this->keepAlive){
        this->state = Contemplates;
        this->redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(actionLength));

        this->state = WaitsForEating;
        this->redraw();
        // first fork
        while(!availableForks[0]->TryToPickUp()){
            std::this_thread::sleep_for(forkPickupRetryTime);
        }
        numOfCollectedForks++;
        this->redraw();
        // second fork
        while(!availableForks[1]->TryToPickUp()){
            std::this_thread::sleep_for(forkPickupRetryTime);
        }
        numOfCollectedForks++;

        this->state = Eats;
        this->redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(actionLength));
        availableForks[0]->PutDown();
        availableForks[1]->PutDown();
    }
}

void Philosopher::iconGenerator(int finalObjX, int finalObjY)
{
    if (state == Contemplates)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Cont.");
    }
    else if (state == WaitsForEating)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Waits");
    }
    else if (state == Eats)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Eats");
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (x == 0 || x == width - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '#');
            }

            if (y == 0 || y == height - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '#');
            }

            if (x == 1 && y == 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, 'P');
            }
        }
    }
}