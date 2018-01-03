#include "snake.hpp"

Snake::Snake(void){
  BodyList tmp;
  tmp.type = "head";
  tmp.x = 10;
  tmp.y = 10;
  this->bodyList.push_back(tmp);
  this->end = this->bodyList.end();
  this->start = this->bodyList.begin();
  this->isRestart = false;

  return;
}

Snake::Snake(int w, int h) {
  BodyList tmp;
  tmp.type = "head";
  tmp.x = w/2;
  tmp.y = h/2;
  tmp.dirrection = "S";
  this->bodyList.push_back(tmp);
  for (size_t i = 0; i < 4; i++) {
    tmp.type = "body";
    tmp.x = w/2;
    tmp.y = tmp.y -20;
    this->bodyList.push_back(tmp);
  }
  tmp.type = "fruit";
  tmp.x = rand() % (w - 20 + 1) + 20;
  tmp.y = rand() % (h - 20 + 1) + 20;
  this->bodyList.push_back(tmp);

  this->end = this->bodyList.end();
  this->start = this->bodyList.begin();
  this->reapt = &Snake::south;
  this->isRestart = false;
  this->score = 0;
  this->isMoving = false;
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


Snake::~Snake(void) {
  return;
}

std::list<BodyList>::iterator Snake::nord(std::list<BodyList>::iterator body) {
  body->y = body->y - 20;
  this->isMoving = false;

  return body;
}
std::list<BodyList>::iterator Snake::south(std::list<BodyList>::iterator body) {
  body->y = body->y + 20;
  this->isMoving = false;

  return body;
}

std::list<BodyList>::iterator Snake::east(std::list<BodyList>::iterator body) {
  body->x = body->x + 20;
  this->isMoving = false;

  return body;
}

std::list<BodyList>::iterator Snake::ouest(std::list<BodyList>::iterator body) {
  body->x = body->x - 20;
  this->isMoving = false;
  return body;
}

void Snake::movement(int wich, int w, int h) {

  std::list<BodyList>::iterator start;
  BodyList tmpMaille;
  BodyList newHeadPose;
  tmpMaille.x = -1;
  tmpMaille.y = -1;

  for (start = this->bodyList.begin(); start != this->end; ++start)
  {
    if (start->type == "head") {
      tmpMaille.y = start->y;
      tmpMaille.x = start->x;

      if (wich == 1 && start->dirrection != "S" && start->dirrection != "N") { this->reapt = &Snake::south; start->dirrection = "S"; }
      else if (wich == 2 && start->dirrection != "N" && start->dirrection != "S") { this->reapt = &Snake::nord; start->dirrection = "N"; }
      else if (wich == 3 && start->dirrection != "O" && start->dirrection != "E") { this->reapt = &Snake::ouest; start->dirrection = "O"; }
      else if (wich == 4 && start->dirrection != "E" && start->dirrection != "O") { this->reapt = &Snake::east; start->dirrection = "E"; }
      else { start = (this->*reapt)(start); }
      newHeadPose.x = start->x;
      newHeadPose.y = start->y;
      if (newHeadPose.x < 20 || newHeadPose.y < 20 || newHeadPose.x > w - 20 || newHeadPose.y > h -20 ) {
        this->isRestart = true;
      }

    } else if (start->type == "fruit") {
      if (newHeadPose.x <= start->x + 20 && newHeadPose.x >= start->x - 20  && newHeadPose.y <= start->y + 20 && newHeadPose.y >= start->y - 20) {
        start->x = rand() % (w - 20 + 1) + 20;
        start->y = rand() % (h - 20 + 1) + 20;
        BodyList last  = this->bodyList.back();
        BodyList tmp;
        tmp.type = "body";
        if (last.dirrection == "S") { tmp.x = last.x; tmp.y = last.y - 8; }
        if (last.dirrection == "N") { tmp.x = last.x; tmp.y = last.y + 8; }
        if (last.dirrection == "E") { tmp.x = last.x + 8; tmp.y = last.y; }
        if (last.dirrection == "O") { tmp.x = last.x - 8; tmp.y = last.y; }

        this->bodyList.push_back(tmp);
        this->score = this->score + 10;
      }

    } else {
      int x = tmpMaille.x;
      int y = tmpMaille.y;
      tmpMaille.x = start->x;
      tmpMaille.y = start->y;
      start->x = x;
      start->y = y;
      if (newHeadPose.x <= tmpMaille.x  && newHeadPose.x >= tmpMaille.x   && newHeadPose.y <= tmpMaille.y  && newHeadPose.y >= tmpMaille.y ) {
        this->isRestart = true;
      }
    }
  }
}
