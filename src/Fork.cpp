#include "Fork.h"
#include <curses.h>
#include "Globals.h"

Fork::Fork(RefPoint *refpoint) : VisibleObject(refpoint)
{
    this->width = 3;
    this->height = 3;
}

bool Fork::TryToPickUp()
{
    if (this->mtx.try_lock())
    {
        // not locked

        state = Taken;
        this->redraw();

        return true;
    }
    else
    {
        return false;
    }
}

void Fork::PickUpSync()
{
    this->mtx.lock();
    state = Taken;
    this->redraw();
}

void Fork::PutDown()
{
    this->mtx.unlock();
    state = Free;
    this->redraw();
}

void Fork::iconGenerator(int finalObjX, int finalObjY)
{
    attron(COLOR_PAIR(FORK_COLOR));

    if (state == Free)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Free");
        attron(COLOR_PAIR(FREE_COLOR));
    }
    else if (state == Taken)
    {
        mvprintw(finalObjY - 1, finalObjX, "%s", "Taken");
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (x == 0 || x == width - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '@');
            }

            if (y == 0 || y == height - 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, '@');
            }

            if (x == 1 && y == 1)
            {
                mvaddch(finalObjY + y, finalObjX + x, 'F');
            }
        }
    }

    if (state == Free)
    {
        attron(COLOR_PAIR(FREE_COLOR));
    }

    attroff(COLOR_PAIR(FORK_COLOR));
}