#include "initialisation.hpp"
#include <future>
#include <unistd.h>

Initialisation::Initialisation(void){

  return;
}
Initialisation::Initialisation(int w, int h) {

  initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	curs_set(0); // hide cursor
	notimeout(stdscr, TRUE);
	scrollok(stdscr, FALSE);
  nodelay(stdscr, TRUE);

	WINDOW *boite;
	w = 50;
	h = 70;
	initscr();
	boite= subwin(stdscr, w, h, 0, 0);
	wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(boite);
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

  //usleep(50000);
  usleep(199000);
  return order;
}

int Initialisation::draw(Snake *snake) const {

std::list<BodyList>::const_iterator start;
  for (start = snake->bodyList.begin(); start != snake->end; ++start)
  {

    if (start->type == "fruit") {

      move(start->y, start->x);  // Déplace le curseur tout en bas à droite de l'écran
  		addch('o');
     }
    else {
      move(start->y, start->x);  // Déplace le curseur tout en bas à droite de l'écran
      addch('#');
    }
  }
  refresh();
  // sf::Text text;
  // sf::Font font;
  // if (!font.loadFromFile("ressources/arial.ttf"))
  // {
  //   std::cout << "SFML Erreur when load Font" << '\n';
  //   exit(EXIT_FAILURE);
  // }
  // text.setFont(font);
  // std::stringstream score;
  // score << "Score: " << std::to_string(snake->score);
  // std::string s = score.str();
  // text.setString(s);
  // text.setPosition(10,10);
  // text.setCharacterSize(24);
  // text.setFillColor(sf::Color::White);
  // text.setStyle(sf::Text::Bold);
  // this->win->draw(text);
  // this->win->display();
  return 0;
}
void Initialisation::updateIsStart() {
  this->isStart = true;
  //this->isStart = !this->isStart;
}
void Initialisation::forcePause() const {
  Initialisation* ptr =  const_cast<Initialisation*>(this);
  ptr->isStart = true;
}


int Initialisation::update(Snake *part) const {
  char ch;
  ch = getch();
  //std::cout << "Ch => "<<ch << '\n';
  if (getch() == 27) {
    endwin();
    exit(EXIT_FAILURE);
  }
  if (getch() == KEY_DOWN) { part->isMoving = true; return 1; }
  if (getch() == KEY_UP) { part->isMoving = true; return 2; }
  // if (getch() == KEY_LEFT) { part->isMoving = true; return 1; }
  // if (getch() == KEY_RIGHT) { part->isMoving = true; return 2; }

  if (getch() == 10) {
    const_cast<Initialisation*>(this)->updateIsStart(); return 10;
  }
  // sf::Event event;
  // while (this->win->pollEvent(event))
  // {
  // //  std::cout << this->win->pollEvent(event) << '\n';
  //   if (event.type == sf::Event::Closed) { this->win->close(); return -1; }
  //   if (event.type == sf::Event::KeyPressed) {
  //     if (event.key.code == sf::Keyboard::Escape) { this->win->close(); return -1; }
  //     std::cout << "keycode = " << event.key.code<< '\n';
  //         std::cout << part->isMoving << event.key.code<< '\n';
  //     if (event.key.code == 28) { return 201; }
  //     if (event.key.code == 74 && this->isStart && !part->isMoving) { part->isMoving = true; return 1; }
  //     if (event.key.code == 73 && this->isStart && !part->isMoving) { part->isMoving = true; return 2; }
  //     if (event.key.code == 71 && this->isStart && !part->isMoving) { part->isMoving = true; return 3; }
  //     if (event.key.code == 72 && this->isStart && !part->isMoving) { part->isMoving = true; return 4; }
  //     if (event.key.code == 58) { const_cast<Initialisation*>(this)->updateIsStart(); return 10; }
  //
  //   }
  // }
  if (this->isStart) { return this->interval(100);}
  else { return  -5; }
}

int Initialisation::drawMenu() const {
  return 0;
}

Initialisation::~Initialisation(void) {
  //this->win->close();
  return;
}

Initialisation *createBorde(int h, int w) {
  return new Initialisation(h,w);
}

void stopGame(Initialisation *game) {
  delete game;
}
