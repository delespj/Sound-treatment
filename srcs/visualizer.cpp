#include <iostream>
#include <math.h>
#include "visualizer.hh"

Visualizer::Visualizer(int width, int height)
{
  this->window = NULL;
  this->width = width;
  this->height = height;
  this->x = 0;
  this->y = 0;

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

float	degToRad(float corner)
{
  return (corner * M_PI / 180);
}

void	Visualizer::initPixels()
{
  this->x = 0;
  this->y = ((this->height / 2) / 4) * 3;
  this->x0 = this->x * cos(degToRad(CORNER * 0.0)) - this->y * sin(degToRad(CORNER * 0.0)) + (this->width / 2);
  this->y0 = this->y * cos(degToRad(CORNER * 0.0)) + this->x * sin(degToRad(CORNER * 0.0)) + (this->height / 2);
  this->color[0] = 121;
  this->color[1] = 28;
  this->color[2] = 248;
  this->color[3] = 0;
}

void	Visualizer::drawCircle()
{
  this->initPixels();
  for (float i = 0.0; i < NB_POINTS; i++)
    {
      this->x1 = this->x * cos(degToRad(CORNER * i)) - this->y * sin(degToRad(CORNER * i)) + (this->width / 2);
      this->y1 = this->y * cos(degToRad(CORNER * i)) + this->x * sin(degToRad(CORNER * i)) + (this->height / 2);
      this->drawPoint(this->color, this->x1, this->y1);
      if (i == 1.0 || i == 2.0)
	{
  std::cout << "x0 : " << this->x0 << std::endl;
  std::cout << "y0 : " << this->y0 << std::endl;
  std::cout << "x1 : " << this->x1 << std::endl;
  std::cout << "y1 : " << this->y1 << std::endl;
	}
      SDL_RenderDrawLine(this->renderer, this->x0, this->y0, this->x1, this->y1);
      this->x0 = x1;
      this->y0 = y1;
    }
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
