#include <iostream>
#include "visualizer.hh"

Visualizer::Visualizer(int width, int height)
{
  this->window = NULL;
  this->width = width;
  this->height = height;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cout << "Error : can't init the SDL" << std::endl;
      return;
    }
  SDL_CreateWindowAndRenderer(this->width, this->height, 0, &this->window, &this->renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
}

Visualizer::~Visualizer()
{
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void	Visualizer::drawPoint(int color[4], int x, int y)
{
  SDL_SetRenderDrawColor(this->renderer, color[0], color[1], color[2], color[3]);
  SDL_RenderDrawPoint(this->renderer, x, y);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 0);
}

void	Visualizer::display()
{
  SDL_RenderPresent(this->renderer);
  SDL_UpdateWindowSurface(this->window);
}

void	Visualizer::loop()
{
  while (42)
    if (SDL_PollEvent(&this->event) && this->event.type == SDL_QUIT)
      break;
}
