#ifndef SO2_PROJEKT_PHILISOPHER
#define SO2_PROJEKT_PHILISOPHER

#include "RefPoint.h"
#include "VisibleObject.h"
#include "Fork.h"
#include <vector>

enum PhilosopherState
{
    Contemplates,
    WaitsForEating,
    Eats
};

class Philosopher : public VisibleObject
{
private:
    PhilosopherState state = Contemplates;
    std::vector<Fork *> availableForks;
    bool keepAlive = true;
    int numOfCollectedForks = 0;
    bool leftForkTaken = false;
    bool rightForkTaken = false;

public:
    int waitingTime = 0;
    int eatingPercent = 0;
    Philosopher(RefPoint *refpoint) : VisibleObject(refpoint) {}
    void iconGenerator(int finalObjX, int finalObjY);
    void AssignFork(Fork *fork);
    void SimulateLife(int eatingTime, int contemplatingTime);
    PhilosopherState GetState();
    void Kill();
};

#endif //SO2_PROJEKT_PHILISOPHER