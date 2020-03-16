#include "Fork.h"

bool Fork::TryToPickUp(){
    if(this->mtx.try_lock()){
        // not locked

        state = Taken;
        this->draw();
    }
}

void Fork::PutDown(){
    this->mtx.unlock();
    this->draw();
}