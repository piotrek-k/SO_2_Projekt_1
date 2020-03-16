#include <iostream>
#include "VisibleObject.h"
#include "Philosopher.h"
#include "Fork.h"
#include "RefPoint.h"
#include "Table.h"
#include <curses.h>
#include <vector>

int main()
{
	initscr(); /* Start curses mode 		  */

	std::vector<VisibleObject *> objects;
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
			firstPhilosopher->AssignFork(lastFork);
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

	for (int a = 0; a < 10; a++)
	{
		objects[a]->redraw();
	}

	refresh(); /* Print it on to the real screen */
	getch();   /* Wait for user input */
	endwin();
	return 0;
}