# ifndef GAMEINTERFACE_HPP
# define GAMEINTERFACE_HPP


#include <iostream>
#include <sstream>
#include "snake.hpp"

//#include <SFML/Graphics.hpp>

class GameInterface {
public:
  //virtual sf::RenderWindow& CreateWin() const = 0;
  virtual ~GameInterface() {};
  virtual int update() const = 0;
  virtual int draw(Snake *part) const = 0;
  virtual int drawMenu() const = 0;
  virtual int interval(int order) const = 0;
//  virtual void stopGame() const = 0;
};

//GameInterface::~GameInterface() {};
#endif
