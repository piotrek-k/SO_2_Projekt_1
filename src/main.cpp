#include <iostream>
#include "VisibleObject.h"
#include "Philosopher.h"
#include "Fork.h"
#include "RefPoint.h"
#include "Table.h"
#include <curses.h>
#include <vector>
#include <thread>

#include "Globals.h"

static void newThread(Philosopher *philObj)
{
	philObj->SimulateLife();
}

int main()
{
	initscr(); /* Start curses mode 		  */
	start_color();
	init_pair(PHILOSOPHER_COLOR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(FORK_COLOR, COLOR_CYAN, COLOR_BLACK);
	init_pair(WAITING_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(EATING_COLOR, COLOR_GREEN, COLOR_BLACK);

	std::vector<VisibleObject *> objects;
	std::vector<std::thread *> threads;
	Table t = Table(30, 15, 10, 2.0, 1.0);

	Philosopher *firstPhilosopher = NULL;
	Fork *lastFork = NULL;
	for (int a = 0; a < 5; a++)
	{
		RefPoint *philRef = new RefPoint(0, 0);
		Philosopher *philObj = new Philosopher(philRef);
		objects.push_back(philObj);
		t.AddElement(philRef);
		if (lastFork != NULL)
		{
			philObj->AssignFork(lastFork);
		}

		if (firstPhilosopher == NULL)
		{
			firstPhilosopher = philObj;
		}

		RefPoint *forkRef = new RefPoint(0, 0);
		Fork *forkObj = new Fork(forkRef);
		objects.push_back(forkObj);
		t.AddElement(forkRef);
		lastFork = forkObj;

		philObj->AssignFork(forkObj);
	}
	if (firstPhilosopher != NULL)
	{
		firstPhilosopher->AssignFork(lastFork);
	}

	for (auto &obj : objects)
	{
		if (Philosopher *p = dynamic_cast<Philosopher *>(obj))
		{
			std::thread *n_t = new std::thread(newThread, p);
			threads.push_back(n_t);
		}
	}

	while (true)
	{
		clear();

		for (int a = 0; a < 10; a++)
		{
			objects[a]->redraw();
		}

		refresh(); /* Print it on to the real screen */

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//getch();   /* Wait for user input */
	endwin();
	return 0;
}