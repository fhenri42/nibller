#include <ncurses.h>
int main()
{
	int ch;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	curs_set(0); // hide cursor
	notimeout(stdscr, TRUE);
	scrollok(stdscr, FALSE);
  getch();

  Transforme *transform =  new Transforme();
    Image *image = new Image();
  int length = (*image).getDim().y;
 int y = (*transform).getVert().x;
 int x = (*transform).getHor().x;
 for (int i = 0; i < length; ++i)
 {
     mvprintw(y + i, x,(*image).image[i].c_str());
 }
endwin();
return 0;
}
