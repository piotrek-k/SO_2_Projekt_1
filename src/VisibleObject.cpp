#include "VisibleObject.h"
#include <curses.h>

VisibleObject::VisibleObject(RefPoint *rp)
{
    this->refPoint = rp;
}

void VisibleObject::iconGenerator(int finalObjX, int finalObjY)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (x == 0 || x == width - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '*');
            }

            if (y == 0 || y == height - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '*');
            }
        }
    }
}

void VisibleObject::redraw()
{
    auto pos = this->refPoint->getPosition();
    int finalX = this->posToRefX + std::get<0>(pos);
    int finalY = this->posToRefY + std::get<1>(pos);

    iconGenerator(finalX, finalY);

    refresh();
}