# ifndef GAME_HPP
# define GAME_HPP


#include <dlfcn.h>
#include "gameInterface.hpp"

class Game {

public:

  Game(void);
  Game(int x, int y);
  Game(Game const &src); // Copy
  ~Game(void); // Destructeur de recopie
  GameInterface *realoadLib(int w, int h);
  void current(GameInterface *iGame, void (*dell)(GameInterface*),int w, int h);
  Game &operator=(Game const & src);  // operator d'affecationt
  std::string currentLib;

};

#endif
