#ifndef SO2_PROJEKT_FORK
#define SO2_PROJEKT_FORK

#include "RefPoint.h"
#include "VisibleObject.h"
#include <mutex>
#include <condition_variable>
#include <queue>

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
    std::queue<std::condition_variable> cv;
    int id = -1;

public:
    Fork(RefPoint *refpoint, int id);
    void iconGenerator(int finalObjX, int finalObjY);
    void PickUpSync();
    void PutDown();
    int GetId();
};

#endif //SO2_PROJEKT_FORK