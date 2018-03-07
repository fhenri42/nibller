#include "initialisation.hpp"
#include <future>
#include <unistd.h>

Initialisation::Initialisation(void){

  return;
}
Initialisation::Initialisation(int h, int w) {

    this->h = h;
    this->w = w;
    this->isStart = false;


    initscr();			/* Start curses mode 		*/
    raw();				/* Line buffering disabled	*/
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();			/* Don't echo() while we do getch */
    curs_set(0); // hide cursor
    notimeout(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);


    h = h / 10;
    w = w / 20;

    int mx=0, my=0;
    getmaxyx(stdscr, mx, my);
    if (mx + 20 < h || my + 20 < w) { throw std::logic_error( "Size of window is too little."); }

    initscr();
    this->gameBoite = subwin(stdscr, w, h, 1, 1);
    wborder(this->gameBoite, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(this->gameBoite);

return;
}

Initialisation::Initialisation(Initialisation const &src) {
  (void)(src);
  return;
}

Initialisation &Initialisation::operator=(Initialisation const & src) {
  (void)(src);
  return *this;
}

int Initialisation::interval(int order) const {

  usleep(50000);
  return order;
}

int Initialisation::draw(Snake *snake) const {
  wclear(this->gameBoite);
  std::list<BodyList>::const_iterator start;
  for (start = snake->bodyList.begin(); start != snake->end; ++start)
  {

    if (start->type == "fruit") { mvwprintw(this->gameBoite, start->y / 20, start->x / 10, "o"); }
    else { mvwprintw(this->gameBoite, start->y / 20, start->x / 10, "#"); }
    wrefresh(this->gameBoite);

  }
  wborder(this->gameBoite, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(this->gameBoite);
  return 0;
}
void Initialisation::updateIsStart() {
  //  this->isStart = true;
  this->isStart = !this->isStart;
}
void Initialisation::forcePause() const {
  Initialisation* ptr =  const_cast<Initialisation*>(this);
  ptr->isStart = true;
}


int Initialisation::update(Snake *part) const {
  int ch = getch();
  if (ch == 27) {
    endwin();
    exit(EXIT_FAILURE);
  }
  if (ch == KEY_DOWN && this->isStart && !part->isMoving) { part->isMoving = true; return 1; }
  if (ch == KEY_UP && this->isStart && !part->isMoving) { part->isMoving = true; return 2; }
  if (ch == KEY_LEFT && this->isStart && !part->isMoving) { part->isMoving = true; return 3; }
  if (ch == KEY_RIGHT && this->isStart && !part->isMoving) { part->isMoving = true; return 4; }
  if (ch == 49) { endwin(); return 200; }
  if (ch == 50) { endwin(); return 201; }
  if (ch == 10) { const_cast<Initialisation*>(this)->updateIsStart(); return 10; }
  if (this->isStart) { return this->interval(100); }
  else { return  -5; }
}

int Initialisation::drawMenu() const {
  return 0;
}

Initialisation::~Initialisation(void) {
  endwin();
  return;
}

Initialisation *createBorde(int h, int w) {
try {
  return new Initialisation(h,w);
} catch (const std::exception & e) {
  endwin();

  std::cerr << e.what();
  exit(EXIT_FAILURE);

}
}

void stopGame(Initialisation *game) {
  delete game;
}
