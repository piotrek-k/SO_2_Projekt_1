#include "Philosopher.h"
#include <thread>
#include <chrono> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <exception>

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
        this->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(actionLength));

        this->state = WaitsForEating;
        this->draw();
        // first fork
        while(!availableForks[0]->TryToPickUp()){
            std::this_thread::sleep_for(forkPickupRetryTime);
        }
        numOfCollectedForks++;
        this->draw();
        // second fork
        while(!availableForks[1]->TryToPickUp()){
            std::this_thread::sleep_for(forkPickupRetryTime);
        }
        numOfCollectedForks++;

        this->state = Eats;
        this->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(actionLength));
        availableForks[0]->PutDown();
        availableForks[1]->PutDown();
    }
}