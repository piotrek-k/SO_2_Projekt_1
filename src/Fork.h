#ifndef SO2_PROJEKT_FORK
#define SO2_PROJEKT_FORK

#include "RefPoint.h"
#include "VisibleObject.h"
#include <mutex>

enum ForkState
{
    Free,
    Taken
};

class Fork : public VisibleObject
{
private:
    ForkState state = Free;
    std::mutex mtx;

public:
    Fork(RefPoint *refpoint) : VisibleObject(refpoint) {}
    bool TryToPickUp();
    void PutDown();
};

#endif //SO2_PROJEKT_FORK