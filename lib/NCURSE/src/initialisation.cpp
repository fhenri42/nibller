#include "initialisation.hpp"
#include <future>
#include <unistd.h>

Initialisation::Initialisation(void){
  //  this->win = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Nibller 42");
  return;
}

Initialisation::Initialisation(int w, int h) {

  SDL_Init(SDL_INIT_VIDEO);
  this->h = h;
  this->w = w;
  this->win = SDL_CreateWindow( "Nibller 42 SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
  this->isStart = false;


  this->menuRender = SDL_CreateRenderer(this->win, -1, 0);
  SDL_Surface * image = SDL_LoadBMP("ressources/menu.bmp");
  SDL_Texture * texture = SDL_CreateTextureFromSurface(this->menuRender, image);
  SDL_RenderCopy(this->menuRender, texture, NULL, NULL);
  SDL_RenderPresent(this->menuRender);
  this->gameRender = NULL;
  // SDL_DestroyTexture(texture);
  // SDL_FreeSurface(image);
  // SDL_DestroyRenderer(renderer);
  return;
}

Initialisation::Initialisation(Initialisation const &src) {
  (void)(src);
  return;
}

Initialisation &Initialisation::operator=(Initialisation const & src) {
  (void)(src);
  return *this;
}

int Initialisation::interval(int order) const {

  usleep(50000);
  return order;
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, int w, int h, std::string text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
  int text_width;
  int text_height;
  SDL_Surface *surface;
  SDL_Color textColor = {255, 255, 255, 0};

  surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  text_width = w;
  text_height = h;
  SDL_FreeSurface(surface);
  rect->x = x;
  rect->y = y;
  rect->w = text_width;
  rect->h = text_height;
}


int Initialisation::draw(Snake *snake) const {

  if (this->gameRender != NULL) { SDL_DestroyRenderer(this->gameRender); }
  if (this->menuRender != NULL) { SDL_DestroyRenderer(this->menuRender); }

  TTF_Init();
  TTF_Font *font = TTF_OpenFont("ressources/arial.ttf", 65);
  SDL_Rect rect1;
  SDL_Texture *texture1;


  Initialisation* ptr =  const_cast<Initialisation*>(this);
  ptr->gameRender = SDL_CreateRenderer(this->win, -1, 0);
  SDL_Surface * board = SDL_LoadBMP("ressources/grennBoard.bmp");
  SDL_Texture * textureBoard = SDL_CreateTextureFromSurface(this->gameRender, board);


  SDL_Surface * frut = SDL_LoadBMP("ressources/bana.bmp");
  SDL_Texture * texturefrut = SDL_CreateTextureFromSurface(this->gameRender, frut);
  SDL_Rect SrcR;
  SDL_Rect DestR;
  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = 10;
  SrcR.h = 10;

  DestR.x = 640 / 2 - 10 / 2;
  DestR.y = 580 / 2 - 10 / 2;
  DestR.w = 20;
  DestR.h = 20;

  SDL_Surface * body = SDL_LoadBMP("ressources/body.bmp");
  SDL_Texture * textureBody = SDL_CreateTextureFromSurface(this->gameRender, body);


  std::list<BodyList>::const_iterator start;

  std::stringstream score;
  score << "Score: " << std::to_string(snake->score);
  std::string s = score.str();
  get_text_and_rect(this->gameRender, 0, 0, 100, 30, s, font, &texture1, &rect1);
  SDL_RenderCopy(this->gameRender, textureBoard, NULL, NULL);
  SDL_RenderCopy(this->gameRender, texture1, NULL, &rect1);


  for (start = snake->bodyList.begin(); start != snake->end; ++start)
  {
    DestR.x = start->x;
    DestR.y = start->y;
    if (start->type == "fruit") {

      SDL_RenderCopy(this->gameRender, texturefrut, NULL, &DestR);
    }
    else {
      SDL_RenderCopy(this->gameRender, textureBody, NULL, &DestR);
    }
  }
  SDL_RenderPresent(this->gameRender);
  return 0;
}
void Initialisation::updateIsStart() {
  this->isStart = !this->isStart;
}

void Initialisation::forcePause() const {
  Initialisation* ptr =  const_cast<Initialisation*>(this);
  ptr->isStart = true;
}

int Initialisation::update(Snake *part) const {
  SDL_Event event = {0};
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT) {  SDL_Quit(); return -1; }
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {  SDL_Quit(); return -1; }
      if (event.key.keysym.sym == SDLK_1) { return 200; }
      if (event.key.keysym.sym == SDLK_DOWN && this->isStart && !part->isMoving) { part->isMoving = true; return 1; }
      if (event.key.keysym.sym == SDLK_UP && this->isStart && !part->isMoving) { part->isMoving = true; return 2; }
      if (event.key.keysym.sym == SDLK_LEFT && this->isStart && !part->isMoving) { part->isMoving = true; return 3; }
      if (event.key.keysym.sym == SDLK_RIGHT && this->isStart && !part->isMoving) { part->isMoving = true; return 4; }
      if (event.key.keysym.sym == SDLK_RETURN) {

        const_cast<Initialisation*>(this)->updateIsStart(); return 10; }

      }
    }
    if (this->isStart) { return this->interval(100); }
    else { return  -5; }
  }

  int Initialisation::drawMenu() const {
    return 0;
  }

  Initialisation::~Initialisation(void) {
    SDL_DestroyRenderer(this->gameRender);
    SDL_DestroyRenderer(this->menuRender);
    SDL_DestroyWindow(this->win);

    //SDL_Quit();
    return;
  }

  Initialisation *createBorde(int h, int w) {
    return new Initialisation(h,w);
  }

  void stopGame(Initialisation *game) {
    delete game;
  }
