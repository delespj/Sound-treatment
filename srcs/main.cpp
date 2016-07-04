#include "visualizer.hh"

int     main()
{
  Visualizer	vis(800, 600);

  vis.drawCircle();
  vis.display();
  vis.loop();
  return (0);
}
