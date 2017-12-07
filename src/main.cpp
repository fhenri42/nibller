#include <iostream>
#include <dlfcn.h>
#include "game.hpp"


void dlerror_wrapper(void) {
  std::cout << "error on Dl: " <<dlerror() << '\n';
  exit(EXIT_FAILURE);
}
int main (int argc, char **argv) {


  void *dlHandle;
  GameInterface *(*init)(int, int);
  void (*dell)(GameInterface*);
  GameInterface *iGame;
  Game          game;


  if (argc != 4) { std::cout << "Rember ./nibler [LIBNAME][W][H]" << '\n'; return 0; }
  if (atoi(argv[2]) < 300 || atoi(argv[2]) > 1000 || atoi(argv[3]) < 300 || atoi(argv[3]) > 1000 ) { std::cout << "W or H must be beetween 300 and 1000" << '\n'; return 0; }

  dlHandle = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);

  init = (GameInterface*(*)(int, int))dlsym(dlHandle, "createBorde");

  dell = (void(*)(GameInterface*))dlsym(dlHandle, "stopGame");

  if (!init) { dlerror_wrapper(); }
  if (!dell) { dlerror_wrapper(); }

  iGame = init(atoi(argv[2]), atoi(argv[3]));
  game.current(iGame, dell, atoi(argv[2]), atoi(argv[3]));


  dlclose(dlHandle);
}
