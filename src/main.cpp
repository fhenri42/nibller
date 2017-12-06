#include <iostream>
//#include <list>
#include "../lib/SFML/include/GameInterface.hpp"
#include <dlfcn.h>
#include "game.hpp"


void dlerror_wrapper(void) {
  std::cout << "error on Dl: " <<dlerror() << '\n';
  exit(EXIT_FAILURE);
}
int main (int argc, char **argv) {


  void *dlHandle;
  GameInterface *(*init)(int, int);
  GameInterface *iGame;
  Game          game;


  if (argc != 4) { std::cout << "Rember ./nibler [LIBNAME][H][W]" << '\n'; return 0; }

  dlHandle = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);

  init = (GameInterface*(*)(int, int))dlsym(dlHandle, "createBorde");

  if (!init) { dlerror_wrapper(); }

  iGame = init(atoi(argv[2]), atoi(argv[3]));
  game.current(iGame,atoi(argv[2]), atoi(argv[3]));


  dlclose(dlHandle);
}
