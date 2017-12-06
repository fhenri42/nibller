# ifndef GAME_HPP
# define GAME_HPP

#include <string>
#include <list>

#include <iostream>
#include <sstream>
#include <regex>
#include <limits>
#include "snake.hpp"
#include "../lib/SFML/include/GameInterface.hpp"


class Game {

public:

  Game(void);
  Game(int x, int y);
  Game(Game const &src); // Copy
  ~Game(void); // Destructeur de recopie

  void current(GameInterface *iGame, int w, int h);
  Game &operator=(Game const & src);  // operator d'affecationt

};

#endif
