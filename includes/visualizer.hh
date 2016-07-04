#ifndef VISUALIZER_HH_
# define VISUALIZER_HH_

#include <SDL2/SDL.h>

#define NB_POINTS 360
#define CORNER 360 / NB_POINTS

class Visualizer
{
private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Event	event;
  int	radius;
  int	x;
  int	y;
  int	x1;
  int	y1;
  int	x2;
  int	y2;
  int	x1o;
  int	y1o;
  int	x2o;
  int	y2o;
  int	width;
  int	height;
  int	color[4];

public:
  Visualizer(int width, int height);
  ~Visualizer();

public:
  void	drawPoint(int color[4], int x, int y); // color[0] : R, 1 : G, 2 : B, 3 : T
  void	drawCircle(int height[180]);
  void	drawLine();

  void	display();
  void	loop(const char*, int);

  void	initPixels(); // tmp
};

#endif
