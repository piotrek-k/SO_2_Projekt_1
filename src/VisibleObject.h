#ifndef SO2_PROJEKT_VISIBLE_OBJECT_H
#define SO2_PROJEKT_VISIBLE_OBJECT_H

#include "RefPoint.h"

class VisibleObject {
private:
    RefPoint* refPoint;
    int posToRefX = 0;
    int posToRefY = 0;
    int width=3;
    int height=3;
public:
    VisibleObject(RefPoint* refpoint);
    void draw();
};

#endif //SO2_PROJEKT_VISIBLE_OBJECT_H