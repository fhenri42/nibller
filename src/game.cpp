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
    /* Get order from libs */
    order = iGame->update(snake);

    /* Check if we need to stop the game */
    if (snake->isRestart) {
      dell(iGame);
      iGame = this->realoadLib(w, h);
      snake->isRestart = false;
      snake = new Snake(w, h);
      order = -2;
    }

    /* Check if the user ask to change lib */
    /* If the user change lib reset params */
    if (order >= 200 && order <= 202) {
    switch (order) {
      case 200:
        this->currentLib = "lib/SFML/bin/sfml.so";
        break;
      case 201:
        this->currentLib = "lib/SDL/bin/sdl.so";
        break;
      case 202:
        this->currentLib = "lib/NCURSE/bin/ncurse.so";
        break;
      default:
        this->currentLib = "lib/SFML/bin/sfml.so";
        break;
    }
      iGame->forcePause();
      dell(iGame);
      iGame = this->realoadLib(w, h);
      iGame->forcePause();
    }

    /* Generate borad and draw it */
    if (order >= 0) {
      snake->movement(order,w, h);
      if (order != 0) { iGame->draw(snake); }
    } else {
      iGame->drawMenu();
    }
  }

}
