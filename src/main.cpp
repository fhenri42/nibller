#include <iostream>
//#include <list>
#include "../lib/SFML/include/GameInterface.hpp"
#include <dlfcn.h>
#include "snake.hpp"


void dlerror_wrapper(void) {
  std::cout << "err"<<dlerror() << '\n';
  exit(EXIT_FAILURE);
}
int main (int argc, char **argv) {

  std::cout << "Hello" << '\n';

  void *dlHandle;
  int order = 0;
  GameInterface *(*init)(int, int);
  GameInterface *game;
  Snake *snake = new Snake(10, 10);

  if(argc != 4) { std::cout << "Rember ./nibler [LIBNAME][H][W]" << '\n'; }
  dlHandle = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);

  init = (GameInterface*(*)(int, int))dlsym(dlHandle, "createBorde");

  if (!init) { dlerror_wrapper(); }
  game = init(atoi(argv[2]), atoi(argv[3]));
  std::list<BodyList>::const_iterator start;

  for (start = snake->bodyList.begin(); start != snake->end; ++start)
{
  //std::cout << start->x << '\n';
}
return 0;

  while (order != -1) {

    order = game->update();
    if (order == 1) {
      /* code */
    }
    //std::cout << "continu"<<continu << '\n';
  }
  std::cout << "end " << '\n';

  dlclose(dlHandle);
}
