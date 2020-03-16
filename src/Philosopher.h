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
    bool keepAlive = false;
    int numOfCollectedForks = 0;

public:
    Philosopher(RefPoint *refpoint) : VisibleObject(refpoint) {}
    void iconGenerator(int finalObjX, int finalObjY);
    void AssignFork(Fork *fork);
    void SimulateLife();
};

#endif //SO2_PROJEKT_PHILISOPHER