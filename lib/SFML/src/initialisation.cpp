//g++ main.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$HOME/.brew/lib



#include "initialisation.hpp"
#include <future>
#include <unistd.h>

Initialisation::Initialisation(void){
  //  sf::RenderWindow win(sf::VideoMode(500, 500), "SFML Test");
  this->win = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML Test");
  return;
}
Initialisation::Initialisation(int h, int w) {
  //  sf::RenderWindow win(sf::VideoMode(h, w), "SFML Test");
  this->h = h;
  this->w = w;
  this->win = new sf::RenderWindow(sf::VideoMode(w, h), "SFML Test");
  this->event = new sf::Event();
  this->lastOrder = 1;

  sf::Texture texture;


  if (!texture.loadFromFile("ressources/snakeHead.png")) {
    std::cout << "Erreur when load texture" << '\n';
  }

  sf::Sprite head;
  head.setTexture(texture);
  this->win->isOpen();

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

  sf::Texture textureHead;
  sf::Texture textureBody;

  if (!textureHead.loadFromFile("ressources/snakeHead.png")) {
    std::cout << "Erreur when load textureHead" << '\n';
  }

  if (!textureBody.loadFromFile("ressources/order_background.jpg")) {
    std::cout << "Erreur when load textureBody" << '\n';
  }
  std::list<BodyList>::const_iterator start;

  this->win->clear();
  for (start = snake->bodyList.begin(); start != snake->end; ++start)
  {
    sf::Sprite snakeText;
    snakeText.move(start->x, start->y);
    if (start->type == "head") { snakeText.setTexture(textureHead);}
    else { snakeText.setTexture(textureBody); }
    this->win->draw(snakeText);
  }
  this->win->display();
  return 0;
}
void Initialisation::updateLastOrder(int order) {
  this->lastOrder = order;
}

int Initialisation::update() const {
  sf::Event event;
  while (this->win->pollEvent(event))
  {
    if (event.type == sf::Event::Closed) { this->win->close(); return -1; }
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) { this->win->close(); return -1; }
      //std::cout << "keycode = " << event.key.code<< '\n';
      if (event.key.code == 74) { const_cast<Initialisation*>(this)->updateLastOrder(1); return 1; }
      if (event.key.code == 73) { const_cast<Initialisation*>(this)->updateLastOrder(2); return 2; }
      if (event.key.code == 71) { const_cast<Initialisation*>(this)->updateLastOrder(3); return 3; }
      if (event.key.code == 72) { const_cast<Initialisation*>(this)->updateLastOrder(4); return 4; }

    }
  }

  return this->interval(100);
}

//  sf::RenderWindow& Initialisation::CreateWin() const{
//   static sf::RenderWindow win(sf::VideoMode(this->h, this->w), "Nibler");
//
//   return win;
// }

Initialisation::~Initialisation(void) {
  return;
}

Initialisation *createBorde(int h, int w) {
  return new Initialisation(h,w);
}
