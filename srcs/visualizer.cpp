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

float	degToRad(int corner)
{
  return ((float)corner * M_PI / 180);
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
  int	x1f;
  int	y1f;
  int y2f;
  int x2f;

  for (int i = 0; i < NB_POINTS; i++)
    {
      tmp = height[j] + this->y;
      this->y1 = tmp * cos(degToRad(CORNER * i)) + this->x * sin(degToRad(CORNER * i)) + (this->height / 2);
      this->x1 = this->x * cos(degToRad(CORNER * i)) - tmp * sin(degToRad(CORNER * i)) + (this->width / 2);
      tmp = this->y - height[j];
      this->y2 = tmp * cos(degToRad(CORNER * i)) + this->x * sin(degToRad(CORNER * i)) + (this->height / 2);
      this->x2 = this->x * cos(degToRad(CORNER * i)) - tmp * sin(degToRad(CORNER * i)) + (this->width / 2);
      this->drawPoint(this->color, this->x1, this->y1);
      this->drawPoint(this->color, this->x2, this->y2);
      if (i != 0)
	{
	  SDL_RenderDrawLine(this->renderer, this->x1o, this->y1o, this->x1, this->y1);
	  SDL_RenderDrawLine(this->renderer, this->x2o, this->y2o, this->x2, this->y2);
	}
      else
	{
	  x1f = this->x1;
	  x2f = this->x2;
	  y1f = this->y1;
	  y2f = this->y2;
	}
      SDL_RenderDrawLine(this->renderer, this->x1, this->y1, this->x2, this->y2);
      this->x2o = x2;
      this->y2o = y2;
      this->x1o = x1;
      this->y1o = y1;
      j++;
    }
  SDL_RenderDrawLine(this->renderer, x1f, y1f, this->x1, this->y1);
  SDL_RenderDrawLine(this->renderer, x2f, y2f, this->x2, this->y2);
  SDL_RenderPresent(this->renderer);
}

void	Visualizer::display()
{
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);
  SDL_UpdateWindowSurface(this->window);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 0);
}

void    init_height(int height[180])
{
  for (int i = 0; i < 180; i++)
    {
      height[i] = random() % 50;
      // if (i % 2 == 0)
      //        height[i] = 50;
      // else
      //        height[i] = 20;
    }
}

#include <unistd.h>

void	Visualizer::loop()
{
  int	height[180];
  while (42)
    {
      init_height(height);
      this->drawCircle(height);
      this->display();
      if (SDL_PollEvent(&this->event) && this->event.type == SDL_QUIT)
	break;
      usleep(200000);
    }
}
