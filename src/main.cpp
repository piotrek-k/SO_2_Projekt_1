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

static void newThread(Philosopher *philObj, int eatingTime, int contemplatingTime)
{
	philObj->SimulateLife(eatingTime, contemplatingTime);
}

static void waitForKey(bool *threadStop)
{
	while (true)
	{
		char key = getch();
		if (key == 'q' || key == 27)
		{
			*threadStop = true;
		}
	}
}

int main(int argc, char *argv[])
{
	initscr(); /* Start curses mode 		  */
	start_color();
	init_pair(PHILOSOPHER_COLOR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(FORK_COLOR, COLOR_CYAN, COLOR_BLACK);
	init_pair(WAITING_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(EATING_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(FREE_COLOR, COLOR_WHITE, COLOR_BLACK);

	std::vector<VisibleObject *> objects;
	std::vector<std::thread *> threads;
	Table t = Table(30, 15, 10, 2.0, 1.0);

	int numOfPhilosophers = 5;
	int eatingTime = 2;
	int contempTime = 3;
	if (argc == 2)
	{
		numOfPhilosophers = atoi(argv[1]);
	}

	if (argc == 4)
	{
		numOfPhilosophers = atoi(argv[1]);
		eatingTime = atoi(argv[2]);
		contempTime = atoi(argv[3]);
	}

	Philosopher *firstPhilosopher = NULL;
	Fork *lastFork = NULL;
	for (int a = 0; a < numOfPhilosophers; a++)
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
			std::thread *n_t = new std::thread(newThread, p, eatingTime, contempTime);
			threads.push_back(n_t);
		}
	}

	bool appStop = false;
	std::thread *n_t = new std::thread(waitForKey, &appStop);
	while (!appStop)
	{
		clear();

		for (auto &obj : objects)
		{
			obj->redraw();
		}

		int position = 30;
		mvprintw(position, 5, "Legenda:");
		mvprintw(position+1, 5, "P - filozof");
		mvprintw(position+2, 5, "F - widelec");
		mvprintw(position+3, 5, "<< - filozof uzywa lewego widelca");
		mvprintw(position+4, 5, ">> - filozof uzywa prawego widelca");
		mvprintw(position+5, 5, "Wcisniecie 'q' lub 'esc' zamyka program");

		refresh(); /* Print it on to the real screen */

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	for (auto &obj : objects)
	{
		if (Philosopher *p = dynamic_cast<Philosopher *>(obj))
		{
			p->Kill();
		}
	}

	int counter = threads.size();
	for (auto &t : threads)
	{
		clear();
		mvprintw(5, 5, "Zamykanie. Oczekiwanie na zakonczenie watkow... (%d/%d)", counter, threads.size());
		refresh();
		t->join();
		counter--;
	}

	//getch();   /* Wait for user input */
	endwin();
	return 0;
}