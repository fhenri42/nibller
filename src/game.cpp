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

GameInterface *Game::realoadLib(int w, int h) {
  void          *dlHandle;
  GameInterface *(*init)(int, int);
  GameInterface *iGame;
  Game          game;

  dlHandle = dlopen(this->currentLib.c_str(), RTLD_LAZY | RTLD_LOCAL);
  init = (GameInterface*(*)(int, int))dlsym(dlHandle, "createBorde");
  iGame = init(w, h);
  return iGame;

}

void Game::current(GameInterface *iGame, void (*dell)(GameInterface*), int w, int h) {

  Snake         *snake = new Snake(w, h);

  int order = -2;
  while (order != -1) {

    order = iGame->update(snake);

    if (snake->isRestart) {
      dell(iGame);
      iGame = this->realoadLib(w, h);
      snake->isRestart = false;
      snake = new Snake(w, h);
      order = -2;
    }
    if (order == 200) {
      this->currentLib = "lib/SFML/bin/sfml.so";
      iGame->forcePause();
      dell(iGame);
      iGame = this->realoadLib(w, h);
      iGame->forcePause();
    }
    if (order == 201) {
      this->currentLib = "lib/SDL/bin/sdl.so";
      iGame->forcePause();
      dell(iGame);
      iGame = this->realoadLib(w, h);
      iGame->forcePause();
    }
    if (order >= 0) {
      if (order == 1) { snake->movement(1,w, h); }
      else if (order == 2) { snake->movement(2,w, h); }
      else if (order == 3) { snake->movement(3,w, h); }
      else if (order == 4) { snake->movement(4,w, h); }
      else if (order == 100) { snake->movement(100,w ,h); }
      if (order != 0) { iGame->draw(snake); }
    } else {
      iGame->drawMenu();
    }
  }

}
