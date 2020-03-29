#include "Fork.h"
#include <curses.h>
#include "Globals.h"

Fork::Fork(RefPoint *refpoint, int id) : VisibleObject(refpoint)
{
    this->width = 3;
    this->height = 3;
    this->id = id;
}

void Fork::PickUpSync()
{
    //this->mtx.lock();
    std::unique_lock<std::mutex> ulock(mtx);
    if (state == Taken)
    {
        cv.emplace(); // dodaj na koniec kolejki
        cv.back().wait(ulock);
    }

    state = Taken;
    this->redraw();
}

void Fork::PutDown()
{
    //this->mtx.unlock();
    std::unique_lock<std::mutex> ulock(mtx);

    if (!cv.empty())
    {
        cv.front().notify_one();
        cv.pop();
    }

    state = Free;
    this->redraw();
}

void Fork::iconGenerator(int finalObjX, int finalObjY)
{
    attron(COLOR_PAIR(FORK_COLOR));

    if (state == Free)
    {
        mvprintw(finalObjY - 1, finalObjX, "(%d) %s", id, "Free");
        attron(COLOR_PAIR(FREE_COLOR));
    }
    else if (state == Taken)
    {
        mvprintw(finalObjY - 1, finalObjX, "(%d) %s", id, "Taken");
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

int Fork::GetId(){
    return id;
}