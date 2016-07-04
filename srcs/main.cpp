#include "visualizer.hh"

void	init_height(int height[180])
{
  for (int i = 0; i < 180; i++)
    {
      if (i % 2 == 0)
	height[i] = 50;
      else
	height[i] = 20;
    }
}

int     main()
{
  Visualizer	vis(800, 600);
  int	height[180];

  init_height(height);
  vis.drawCircle(height);
  vis.display();
  vis.loop();
  return (0);
}
