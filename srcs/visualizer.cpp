#include <iostream>
#include <math.h>
#include "SoundSystem.hh"
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

void	Visualizer::drawCircle(int height[])
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

#include <unistd.h>

void	Visualizer::loop(const char* path, int nb)
{
	//Rather useless defines
	#define SPECTRUMRANGE ((float)OUTPUTRATE / 2.0f) // 24000.0 Hz
	#define BINSIZE (SPECTRUMRANGE / (float)SPECTRUMSIZE) // 5.8594 Hz

	//We do not show the full spectrum, instead just the interesting part
	#define SPECTRUM_START 6 // 41.0156 Hz  (7 * BINSIZE)
	#define SPECTRUM_END 2560 // 15000.0 Hz  (2560 * BINSIZE)
	//Storages for the left and right spectrums
	float spectrumL[SPECTRUMSIZE];
	float spectrumR[SPECTRUMSIZE];

	#define BAR_MULT 1.0165 //Affects the amount of bars -> 360
	int bar_amount = 0; //The amount of bars
	float i = BAR_MULT - 1;
	float start = 0;
	while(start + i <= SPECTRUMSIZE - 1) {
		if(start >= SPECTRUM_START && start + i <= SPECTRUM_END) bar_amount++;
		start+= i;
		i*= BAR_MULT;
	}

	int *bar_start = new int[bar_amount]; //Start of full frequencies
	int *bar_end = new int[bar_amount]; //End of full frequencies
	int *bar_first = new int[bar_amount]; //First non-full frequency
	float *bar_first_mult = new float[bar_amount]; //Mult for first non-full frequency
	int *bar_last = new int[bar_amount]; //Last non-full frequency
	float *bar_last_mult = new float[bar_amount]; //Mult for last non-full frequency

	i = BAR_MULT - 1;
	start = 0;
	while(start < SPECTRUM_START) { //Skip some frequencies
		start+= i;
		i*= BAR_MULT;
	}
	for(int j = 0; j < bar_amount; j++) {
		const float end = start + i;
		bar_start[j] = ceil(start);
		bar_end[j] = floor(end);
		bar_first[j] = floor(start);
		bar_first_mult[j] = bar_start[j] == bar_first[j] ? 0.0 : 1.0 - start + floor(start);
		bar_last[j] = floor(end);
		bar_last_mult[j] = end - floor(end);
		if(bar_first[j] == bar_last[j]) {
			bar_first_mult[j] = end - start;
			bar_last_mult[j] = 0.0;
		}
		start+= i;
		i*= BAR_MULT;
	}




    int* heights;
    SoundSystem* ss = new SoundSystem(path);

    ss->play_music();
    while (42)
    {
        ss->get_spectrum(spectrumL, spectrumR);

        heights = new int[NB_POINTS];

        {
            heights = new int[NB_POINTS];

        	float *bar1_heights = new float[bar_amount];
        	//Calculate the heights for the bars
        	for(int i = 0; i < bar_amount; i++) {
        		float sumL = spectrumL[bar_first[i]] * bar_first_mult[i] + spectrumL[bar_last[i]] * bar_last_mult[i];
        		float sumR = spectrumR[bar_first[i]] * bar_first_mult[i] + spectrumR[bar_last[i]] * bar_last_mult[i];

        		for(int j = bar_start[i]; j < bar_last[i]; j++) {
        			sumL+= spectrumL[j - 1];
        			sumR+= spectrumR[j - 1];
        		}

        		bar1_heights[i] = std::max((sumL + sumR) * 5.0 - 0.04, 0.0) + 0.015;
        	}
        	//Draw the bars
            int i;
        	for(i = 0; i < bar_amount; i++) {
        		// const float x = -1.0 + (float)i / (float)bar_amount * 2.0;
        		// const float x2 = -1.0 + float(i + 1) / (float)bar_amount * 2.0;

                    if (i < NB_POINTS) {
                        heights[i] = bar1_heights[i] * nb;
                    }

        		//Here we actually draw
        		// const float vertices[VERTEX_ARRAY_SIZE * 2] = {
        		// 	x,  -1.0f,
        		// 	x,  -1.0f + height,
        		// 	x2, -1.0f,
        		// 	x2, -1.0f + height};
        		// graphics.draw_arrays(vertices, bars_color);
                // std::cout << height << std::endl;
        	}
            std::cout << "size: " << i << std::endl;
        	delete [] bar1_heights;
        }

        this->drawCircle(heights);
        this->display();

        delete heights;

        if (SDL_PollEvent(&this->event) && this->event.type == SDL_QUIT)
            break;
        ss->update();
        usleep(1000000 / 60);
    }
    delete ss;
}
