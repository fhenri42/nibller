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
	int ch = 0;
	while (1) {
		ch =  getch();
		if (ch == KEY_UP) { i--; }
		if (ch == KEY_DOWN) { i++; }
		if (ch == KEY_LEFT) { y--; }
		if (ch == KEY_RIGHT) { y++; }
		if (ch == 27) {
			endwin();
			exit(EXIT_FAILURE);
		}
		move(i, y);  // Déplace le curseur tout en bas à droite de l'écran
		addch('.');
		//usleep(50000);
		refresh();
	}
endwin();
return 0;
}
