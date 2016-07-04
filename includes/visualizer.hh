#ifndef VISUALIZER_HH_
# define VISUALIZER_HH_

#include <SDL2/SDL.h>

#define CORNER 2.0
#define NB_POINTS 180.0

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
  int	x0;
  int	y0;
  int	width;
  int	height;
  int	color[4];

public:
  Visualizer(int width, int height);
  ~Visualizer();

public:
  void	drawPoint(int color[4], int x, int y); // color[0] : R, 1 : G, 2 : B, 3 : T
  void	drawCircle();
  void	drawLine();

  void	display();
  void	loop();

  void	initPixels(); // tmp
};

#endif
