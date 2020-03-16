#include <iostream>
#include "VisibleObject.h"
#include "RefPoint.h"
#include "Table.h"
#include <curses.h>
#include <vector>

int main()
{
	initscr(); /* Start curses mode 		  */

	std::vector<VisibleObject *> objects;
	Table t = Table(15, 15, 10);
	for (int a = 0; a < 10; a++)
	{
		RefPoint *mainRef = new RefPoint(0, 0);
		VisibleObject *testObj = new VisibleObject(mainRef);
		objects.push_back(testObj);
		t.AddElement(mainRef);
	}
	for (int a = 0; a < 10; a++)
	{
		objects[a]->draw();
	}

	refresh(); /* Print it on to the real screen */
	getch();   /* Wait for user input */
	endwin();
	return 0;
}