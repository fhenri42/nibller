# ifndef SNAKE_HPP
# define SNAKE_HPP

#include <string>
#include <list>

#include <iostream>
#include <sstream>
#include <regex>
#include <limits>

struct BodyList
{
  std::string type;
  std::string dirrection;
  int x;
  int y;
};

class Snake {

public:
  std::list<BodyList> bodyList;
  std::list<BodyList>::iterator start;
  std::list<BodyList>::iterator end;

  Snake(void);
  Snake(int x, int y);
  Snake(Snake const &src); // Copy
  ~Snake(void); // Destructeur de recopie
  std::list<BodyList>::iterator  nord(std::list<BodyList>::iterator body);
  std::list<BodyList>::iterator  south(std::list<BodyList>::iterator body);
  std::list<BodyList>::iterator  east(std::list<BodyList>::iterator body);
  std::list<BodyList>::iterator  ouest(std::list<BodyList>::iterator body);
//  void (MyClass::*func)(int);
  std::list<BodyList>::iterator  (Snake::*reapt)(std::list<BodyList>::iterator body);
  void movement(int wich, int w, int h);
  Snake &operator=(Snake const & src);  // operator d'affecationt

};

#endif
