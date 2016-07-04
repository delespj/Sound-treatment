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
  this->y = 100;
  this->x1o = this->x * cos(degToRad(CORNER * 0.0)) - this->y * sin(degToRad(CORNER * 0.0)) + (this->width / 2);
  this->y1o = this->y * cos(degToRad(CORNER * 0.0)) + this->x * sin(degToRad(CORNER * 0.0)) + (this->height / 2);
  this->color[0] = 121;
  this->color[1] = 28;
  this->color[2] = 248;
  this->color[3] = 0;
}

void	Visualizer::drawCircle(int height[180])
{
  this->initPixels();
  int	j = 0;
  float	tmp = 0.0;
  int	x1f = this->x * cos(degToRad(CORNER * 0)) - (height[0] + this->y)
    * sin(degToRad(CORNER * 0)) + (this->width / 2);
  int	y1f = this->y1 = (height[0] + this->y) * cos(degToRad(CORNER * 0)) + this->x
    * sin(degToRad(CORNER * 0)) + (this->height / 2);
  int y2f = tmp * cos(degToRad(CORNER * 0)) + this->x * sin(degToRad(CORNER * 0)) + (this->height / 2);
  int x2f = this->x * cos(degToRad(CORNER * 0)) - tmp * sin(degToRad(CORNER * 0)) + (this->width / 2);

  for (float i = 0.0; i < NB_POINTS; i++)
    {
      tmp = height[j] + this->y;
      this->y1 = tmp * cos(degToRad(CORNER * i)) + this->x * sin(degToRad(CORNER * i)) + (this->height / 2);
      this->x1 = this->x * cos(degToRad(CORNER * i)) - tmp * sin(degToRad(CORNER * i)) + (this->width / 2);
      tmp = this->y - height[j];
      this->y2 = tmp * cos(degToRad(CORNER * i)) + this->x * sin(degToRad(CORNER * i)) + (this->height / 2);
      this->x2 = this->x * cos(degToRad(CORNER * i)) - tmp * sin(degToRad(CORNER * i)) + (this->width / 2);
      this->drawPoint(this->color, this->x1, this->y1);
      this->drawPoint(this->color, this->x2, this->y2);
      SDL_RenderDrawLine(this->renderer, this->x1o, this->y1o, this->x1, this->y1);
      SDL_RenderDrawLine(this->renderer, this->x2o, this->y2o, this->x2, this->y2);
	   //      SDL_RenderDrawLine(this->renderer, this->x1, this->y1, this->x2, this->y2);
      this->x2o = x2;
      this->y2o = y2;
      this->x1o = x1;
      this->y1o = y1;
      j++;
    }
  SDL_RenderDrawLine(this->renderer, x1f, y1f, this->x1, this->y1);
  SDL_RenderDrawLine(this->renderer, x2f, y2f, this->x2, this->y2);
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
