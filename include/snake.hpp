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
  int x;
  int y;
};

class Snake {

public:
  std::list<BodyList> bodyList;
  std::list<BodyList>::const_iterator start;
  std::list<BodyList>::const_iterator end;

  Snake(void);
  Snake(int x, int y);
  Snake(Snake const &src); // Copy
  ~Snake(void); // Destructeur de recopie

  Snake &operator=(Snake const & src);  // operator d'affecationt

};

#endif
