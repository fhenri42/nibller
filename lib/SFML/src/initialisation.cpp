#include "initialisation.hpp"
#include <future>
#include <unistd.h>

Initialisation::Initialisation(void){
  this->win = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Nibller 42 SFML");
  return;
}
Initialisation::Initialisation(int w, int h) {
  this->h = h;
  this->w = w;
  this->win = new sf::RenderWindow(sf::VideoMode(w, h), "Nibller 42 SFML");
  this->event = new sf::Event();
  this->isStart = false;

  sf::Texture menu;
  if (!menu.loadFromFile("ressources/menu.png")) {
    this->win->close();
    throw std::logic_error( "SFML Erreur when load menu");
  }
  this->win->isOpen();
  sf::Sprite background;
  //background.move(w/2, h/2);
  background.setTexture(menu);

  background.setOrigin((menu.getSize().x / 2) - (w / 2), (menu.getSize().y / 2) - (h / 2));
  this->win->clear();
  this->win->draw(background);
  this->win->display();
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

  sf::Texture textureBody;
  sf::Texture texturefrut;
  sf::Texture board;

  if (!textureBody.loadFromFile("ressources/body.jpg")) {
    this->win->close();
    throw std::logic_error( "SFML Erreur when load textureBody");
  }
  if (!texturefrut.loadFromFile("ressources/bana.png")) {
    this->win->close();
    throw std::logic_error( "SFML Erreur when load textureBana");
  }

  if (!board.loadFromFile("ressources/background.jpg")) {
    this->win->close();
    throw std::logic_error( "SFML Erreur when load board");
  }

  std::list<BodyList>::const_iterator start;

  sf::Sprite background(board);
  background.setOrigin((board.getSize().x / 2) - (this->w / 2), (board.getSize().y / 2) - (this->h / 2));
  this->win->clear();
  this->win->draw(background);
  for (start = snake->bodyList.begin(); start != snake->end; ++start)
  {
    sf::Sprite snakeText;
    snakeText.move(start->x, start->y);
    if (start->type == "fruit") { snakeText.setTexture(texturefrut);}
    else { snakeText.setTexture(textureBody); }
    this->win->draw(snakeText);
  }
  sf::Text text;
  sf::Font font;
  if (!font.loadFromFile("ressources/arial.ttf"))
  {
    this->win->close();
    throw std::logic_error( "SFML Erreur when load Font");
  }
  text.setFont(font);
  std::stringstream score;
  score << "Score: " << std::to_string(snake->score);
  std::string s = score.str();
  text.setString(s);
  text.setPosition(10,10);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  this->win->draw(text);
  this->win->display();
  return 0;
}
void Initialisation::updateIsStart() {
  this->isStart = !this->isStart;
}
void Initialisation::forcePause() const {
  Initialisation* ptr =  const_cast<Initialisation*>(this);
  ptr->isStart = true;
}


int Initialisation::update(Snake *part) const {
  sf::Event event;
  while (this->win->pollEvent(event))
  {
    if (event.type == sf::Event::Closed) { this->win->close(); return -1; }
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) { this->win->close(); return -1; }
      if (event.key.code == 28) { return 201; }
      if (event.key.code == 29) { return 202; }
      if (event.key.code == 74 && this->isStart && !part->isMoving) { part->isMoving = true; return 1; }
      if (event.key.code == 73 && this->isStart && !part->isMoving) { part->isMoving = true; return 2; }
      if (event.key.code == 71 && this->isStart && !part->isMoving) { part->isMoving = true; return 3; }
      if (event.key.code == 72 && this->isStart && !part->isMoving) { part->isMoving = true; return 4; }
      if (event.key.code == 58) { const_cast<Initialisation*>(this)->updateIsStart(); return 10; }

    }
  }
  if (this->isStart) { return this->interval(100);}
  else { return  -5; }
}

int Initialisation::drawMenu() const {
  return 0;
}

Initialisation::~Initialisation(void) {
  this->win->close();
  return;
}

Initialisation *createBorde(int h, int w) {
  try {
    return new Initialisation(h,w);
  } catch (const std::exception & e) {
    std::cerr << e.what();
    exit(EXIT_FAILURE);
  }
  }

void stopGame(Initialisation *game) {
  delete game;
}
