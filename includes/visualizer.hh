#ifndef VISUALIZER_HH_
# define VISUALIZER_HH_

#include <SDL2/SDL.h>

class Visualizer
{
private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Event	event;
  int	width;
  int	height;

public:
  Visualizer(int width, int height);
  ~Visualizer();

public:
  void	drawPoint(int color[4], int x, int y); // color[0] : R, 1 : G, 2 : B, 3 : T
  void	display();
  void	loop();
};

#endif
