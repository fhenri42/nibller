#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <future>
#include <unistd.h>
int main()
{
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	curs_set(0); // hide cursor
	notimeout(stdscr, TRUE);
	scrollok(stdscr, FALSE);

	WINDOW *boite;
	int w = 50;
	int h = 70;
	initscr();
	boite= subwin(stdscr, w, h, 0, 0);
	wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(boite);

	int i = 0;
	int y = 0;

	while (1) {
		if (getch() == KEY_UP) { i++; }
		if (getch() == KEY_DOWN) { y++; }
		if (getch() == 27) {
			endwin();
			exit(EXIT_FAILURE);
		}
		move(i, y);  // Déplace le curseur tout en bas à droite de l'écran
		addch('.');
		//usleep(50000);
		refresh();
	}
	getch();
endwin();
return 0;
}
