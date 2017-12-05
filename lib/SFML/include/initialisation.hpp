# ifndef INITIALISATION_HPP
# define INITIALISATION_HPP

#include <string>
#include <list>

#include <iostream>
#include <sstream>
#include "GameInterface.hpp"
#include <SFML/Graphics.hpp>
#include "../../../include/snake.hpp"

class Initialisation : public GameInterface {

public:

  Initialisation(void);
  Initialisation(int w, int h);
  Initialisation(Initialisation const &src); // Copy
  ~Initialisation(void);                // Destructeur de recopie

  Initialisation &operator=(Initialisation const & src);  // operator d'affecationt
  int update() const;
  int draw(Snake *snake) const;
private:
  int h;
  int w;
  sf::RenderWindow *win;
  sf::Event *event;

};


extern "C" {
  Initialisation *createBorde(int h, int w);
}

#endif
