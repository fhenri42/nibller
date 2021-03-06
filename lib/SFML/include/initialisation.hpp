# ifndef INITIALISATION_HPP
# define INITIALISATION_HPP

#include <string>
#include <list>

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../../../include/gameInterface.hpp"
#include "../../../include/snake.hpp"

class Initialisation : public GameInterface {

public:

  Initialisation(void);
  Initialisation(int w, int h);
  Initialisation(Initialisation const &src); // Copy
  ~Initialisation(void);                // Destructeur de recopie

  Initialisation &operator=(Initialisation const & src);  // operator d'affecationt
  int update(Snake *part) const;
  int draw(Snake *snake) const;
  int interval(int order) const;
  int drawMenu () const;
  void updateIsStart();
  void forcePause() const;
  //void stopGame () const;
private:
  int h;
  int w;
  sf::RenderWindow *win;
  sf::Event *event;
  bool isStart;

};


extern "C" {
  Initialisation *createBorde(int w, int h);

  void            stopGame(Initialisation *game);
}

#endif
