#include "VisibleObject.h"
#include <curses.h>

VisibleObject::VisibleObject(RefPoint *rp)
{
    this->refPoint = rp;
}

void VisibleObject::draw()
{
    auto pos = this->refPoint->getPosition();
    int finalX = this->posToRefX + std::get<0>(pos);
    int finalY = this->posToRefY + std::get<1>(pos);

    // TODO: Draw
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (x == 0 || x == width - 1)
            {
                mvaddch(finalY + y, finalX + x, '*');
            }

            if (y == 0 || y == height - 1)
            {
                mvaddch(finalY + y, finalX + x, '*');
            }
        }
    }
}