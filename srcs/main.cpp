#include <stdlib.h>
#include <iostream>
#include "visualizer.hh"

int     main(int ac, char** av)
{
  Visualizer	vis(800, 600);

  if (ac != 3)
    {
      std::cout << "Usage : ./visualizer [PATH] [MULTIPLIER]" << std::endl;
      return (-1);
    }
  vis.loop(av[1], atoi(av[2]));
  return (0);
}
