#include "snake.hpp"

Snake::Snake(void){
  BodyList tmp;
  tmp.type = "head";
  tmp.x = 10;
  tmp.y = 10;
  this->bodyList.push_back(tmp);
  this->end = this->bodyList.end();
  this->start = this->bodyList.begin();
  std::cout << "AEeOAEuO" << '\n';

  return;
}

Snake::Snake(int x, int y) {
  BodyList tmp;
  tmp.type = "head";
  tmp.x = x;
  tmp.y = y;
  this->bodyList.push_back(tmp);
  this->end = this->bodyList.end();
  this->start = this->bodyList.begin();
  return;
}

Snake::Snake(Snake const &src) {
  (void)(src);
  return;
}

Snake &Snake::operator=(Snake const & src) {
  (void)(src);
  return *this;
}

// void Snake::addBodyPart() {
//   BodyList tmp;
//   tmp.type = "Body";
//   tmp.x = 10;
//   tmp.y = 10;
//   this->bodyList.push_back(tmp);
// }
Snake::~Snake(void) {
  return;
}
