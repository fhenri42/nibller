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
  this->win = SDL_CreateWindow( "Nibller 42", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
  this->isStart = false;

  SDL_Renderer * renderer = SDL_CreateRenderer(this->win, -1, 0);
  SDL_Surface * image = SDL_LoadBMP("ressources/menu.bmp");
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

   SDL_DestroyTexture(texture);
   SDL_FreeSurface(image);
   SDL_DestroyRenderer(renderer);
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

int Initialisation::draw(Snake *snake) const {

  SDL_Renderer * renderer = SDL_CreateRenderer(this->win, -1, 0);
  SDL_Surface * board = SDL_LoadBMP("ressources/background.bmp");
  SDL_Texture * textureBoard = SDL_CreateTextureFromSurface(renderer, board);


  SDL_Surface * frut = SDL_LoadBMP("ressources/bana.bmp");
  SDL_Texture * texturefrut = SDL_CreateTextureFromSurface(renderer, frut);
  // SDL_RenderCopy(renderer, texturefrut, NULL, NULL);
  // SDL_RenderPresent(renderer);


  SDL_Surface * body = SDL_LoadBMP("ressources/body.bmp");
  SDL_Texture * textureBody = SDL_CreateTextureFromSurface(renderer, body);


    std::list<BodyList>::const_iterator start;

    SDL_RenderCopy(renderer, textureBoard, NULL, NULL);
    SDL_RenderPresent(renderer);
    for (start = snake->bodyList.begin(); start != snake->end; ++start)
    {
      SDL_Rect dstrect = { start->x, start->y, 20, 20 };

      if (start->type == "fruit") {
        SDL_RenderCopy(renderer, texturefrut, NULL,&dstrect);
      }
      else {
        SDL_RenderCopy(renderer, textureBody, NULL, &dstrect);
        }
        SDL_RenderPresent(renderer);
    }
  //   sf::Text text;
  //   sf::Font font;
  // if (!font.loadFromFile("ressources/arial.ttf"))
  // {
  //   std::cout << "SFML Erreur when load Font" << '\n';
  //   exit(EXIT_FAILURE);
  // }
  //   text.setFont(font);
  //   std::stringstream score;
  //   score << "Score: " << std::to_string(snake->score);
  //   std::string s = score.str();
  //   text.setString(s);
  //   text.setPosition(100,100);
  //   text.setCharacterSize(24);
  //   text.setFillColor(sf::Color::Red);
  //   text.setStyle(sf::Text::Bold);
  //   this->win->draw(text);
  //   this->win->display();
  return 0;
}
void Initialisation::updateIsStart() {
  this->isStart = !this->isStart;
}

int Initialisation::update() const {
  SDL_Event event = {0};
  while (SDL_WaitEvent(&event))
  {
    if (event.type == SDL_QUIT) {  SDL_Quit(); return -1; }
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {  SDL_Quit(); return -1; }
      //std::cout << "keycode = " << event.key.code<< '\n';
      if (event.key.keysym.sym == SDLK_UP && this->isStart) { return 1; }
      if (event.key.keysym.sym == SDLK_DOWN && this->isStart) { return 2; }
      if (event.key.keysym.sym == SDLK_LEFT && this->isStart) { return 3; }
      if (event.key.keysym.sym == SDLK_RIGHT && this->isStart) { return 4; }
      if (event.key.keysym.sym == SDLK_RETURN) {const_cast<Initialisation*>(this)->updateIsStart(); return 10; }

    }
  }
  if (this->isStart) { return this->interval(100);}
  else { return  -5; }
}

int Initialisation::drawMenu() const {
  return 0;
}

Initialisation::~Initialisation(void) {
  SDL_Quit();
  return;
}

Initialisation *createBorde(int h, int w) {
  return new Initialisation(h,w);
}

void stopGame(Initialisation *game) {
  delete game;
}
