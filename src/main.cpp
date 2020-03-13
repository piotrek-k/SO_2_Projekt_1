#include <iostream>
#include "VisibleObject.h"
#include "RefPoint.h"
#include <curses.h>

int main() {
    initscr();			/* Start curses mode 		  */

	RefPoint* mainRef = new RefPoint(0, 0);
	VisibleObject* testObj = new VisibleObject(mainRef);

	testObj->draw();

	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();
    return 0;
}