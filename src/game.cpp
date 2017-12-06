#include "game.hpp"

Game::Game(void){
  return;
}

Game::Game(Game const &src) {
  (void)(src);
  return;
}

Game &Game::operator=(Game const & src) {
  (void)(src);
  return *this;
}

Game::~Game(void) {
  return;
}

void Game::current(GameInterface *iGame,int w, int h) {

  Snake         *snake = new Snake(w, h);

  int order = 100;
  iGame->draw(snake);
  while (order != -1) {

    order = iGame->update();

    if (order == 1) {snake->movement(1,w, h); order = 100; }
    else if (order == 2) { snake->movement(2,w, h); order = 100; }
    else if (order == 3) { snake->movement(3,w, h); order = 100; }
    else if (order == 4) { snake->movement(4,w, h); order = 100; }
    else if (order == 100) { snake->movement(100,w ,h); }
    if (order != 0) { iGame->draw(snake); }
  }
}
