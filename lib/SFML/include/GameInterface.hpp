# ifndef GAMEINTERFACE_HPP
# define GAMEINTERFACE_HPP


#include <iostream>
#include <sstream>
//#include <SFML/Graphics.hpp>

class GameInterface {
public:
  //virtual sf::RenderWindow& CreateWin() const = 0;
  virtual int update() const = 0;

};

#endif
