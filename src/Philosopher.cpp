#include "Philosopher.h"
#include <thread>
#include <chrono>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <exception>
#include <curses.h>

#include "Globals.h"

void Philosopher::AssignFork(Fork *fork)
{
    this->availableForks.push_back(fork);
}

void WaitingThread(Philosopher *p)
{
    while (p->GetState() == PhilosopherState::WaitsForEating)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p->waitingTime += 1;
        p->redraw();
    }
}

void EatingThread(Philosopher *p, int timeMs)
{
    int timeLeft = timeMs;
    while (timeLeft > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        timeLeft -= 100;

        p->eatingPercent = 100 - (timeLeft / (float)timeMs) * 100;
        p->redraw();
    }
}

void Philosopher::Kill()
{
    this->keepAlive = false;
}

void Philosopher::SimulateLife(int eatingTime, int contemplatingTime)
{
    if (this->availableForks.size() != 2)
    {
        throw "Brak wystarczajacej liczby widelcow";
    }

    //this->keepAlive = true;
    srand(time(NULL));

    while (this->keepAlive)
    {
        float randomNum = (rand() % 10) / (float)10;
        int eatingLength = (eatingTime + randomNum) * 1000;
        int contempLength = (contemplatingTime + randomNum) * 1000;
        auto forkPickupRetryTime = std::chrono::milliseconds(100);

        this->state = Contemplates;
        if (keepAlive)
            this->redraw();

        std::this_thread::sleep_for(std::chrono::milliseconds(contempLength));

        this->state = WaitsForEating;
        std::thread *w_t = new std::thread(WaitingThread, this);
        if (keepAlive)
            this->redraw();

        if (!keepAlive)
        {
            break;
        }
        availableForks[0]->PickUpSync();
        lowerIndexForkTaken = true;
        numOfCollectedForks++;
        availableForks[1]->PickUpSync();
        higherIndexForkTaken = true;
        if (keepAlive)
            this->redraw();
        numOfCollectedForks++;

        this->state = Eats;
        std::thread *e_t = new std::thread(EatingThread, this, eatingLength);
        if (keepAlive)
            this->redraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(eatingLength));
        availableForks[1]->PutDown();
        availableForks[0]->PutDown();
        lowerIndexForkTaken = false;
        higherIndexForkTaken = false;
        numOfCollectedForks = 0;
        waitingTime = 0;
    }
}

PhilosopherState Philosopher::GetState()
{
    return this->state;
}

void Philosopher::iconGenerator(int finalObjX, int finalObjY)
{

    if (state == Contemplates)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Cont.");
    }
    else if (state == WaitsForEating)
    {
        attron(COLOR_PAIR(WAITING_COLOR));
        mvprintw(finalObjY - 1, finalObjX, "%s%d", "Waits ", waitingTime);
        attroff(COLOR_PAIR(WAITING_COLOR));
    }
    else if (state == Eats)
    {
        attron(COLOR_PAIR(EATING_COLOR));
        mvprintw(finalObjY - 1, finalObjX, "%s %d%%", "Eats", eatingPercent);
        attroff(COLOR_PAIR(EATING_COLOR));
    }

    attron(COLOR_PAIR(PHILOSOPHER_COLOR));

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

    if(lowerIndexForkTaken){
        mvprintw(finalObjY + (height/2), finalObjX + width, " (%d)", availableForks[0]->GetId());
    }
    if(higherIndexForkTaken){
        mvprintw(finalObjY + (height/2), finalObjX + width, " (%d)", availableForks[1]->GetId());
    }
    if(lowerIndexForkTaken && higherIndexForkTaken){
        mvprintw(finalObjY + (height/2), finalObjX + width, " (%d)(%d)", availableForks[0]->GetId(), availableForks[1]->GetId());
    }

    attroff(COLOR_PAIR(PHILOSOPHER_COLOR));
}