//g++ main.cpp -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$HOME/.brew/lib



#include "initialisation.hpp"

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

  sf::Texture texture;


  if (!texture.loadFromFile("../ressources/snakeHead.png")) {
    std::cout << "Erreur when load texture" << '\n';
  }

  sf::Sprite head;
//  sf::Event event;
  head.setTexture(texture);

//  while (this->win->isOpen()) {
    // while (this->win->pollEvent(event))
    // {
    //   if (event.type == sf::Event::Closed)
    //   {
    //     this->win->close();
    //   }
    //   if (event.type == sf::Event::KeyPressed) {
    //     if (event.key.code == sf::Keyboard::Escape) { this->win->close(); }
    //     if (event.key.code == 74) {
    //       std::cout << "keycode = " << event.key.code<< '\n';
    //       this->win->clear();
    //       sprite.move(0, 10);
    //       this->win->draw(sprite);
    //       this->win->display();
    //     }
    //
    //   }
  //  }
  //this->win->pollEvent(event);
this->win->isOpen();
    this->win->clear();
    this->win->draw(head);
    this->win->display();
  //f6}
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
int Initialisation::update() const {
    sf::Event event;
  while (this->win->pollEvent(event))
  {
    if (event.type == sf::Event::Closed) { this->win->close(); return -1; }
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) { this->win->close(); return -1; }
      if (event.key.code == 74) {
        std::cout << "keycode = " << event.key.code<< '\n';
        return 1;
        // this->win->clear();
        // sprite.move(0, 10);
        // this->win->draw(sprite);
        // this->win->display();
      }

    }
 }
 return 1;
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
