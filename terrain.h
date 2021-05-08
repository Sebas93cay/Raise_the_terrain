#ifndef TERRAINLIB

#define TERRAINLIB

#include <SDL2/SDL.h>
#include <stdio.h>

typedef struct SDL_Instance
{
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer;
  struct point3d_t **points3d;
} SDL_Instance;

typedef struct point3d_t
{
  int x;
  int y;
  int z;
} point3d_t;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance *instance);
int poll_events();
int getSurface(SDL_Surface **screenSurface, SDL_Instance *instance);
void TheExit(SDL_Instance *instance);

/* utils.c */
point3d_t **init_points3d(void);
void free_points3d(point3d_t **points);
void draw3dpoints(SDL_Instance *instance, point3d_t **points);

/*  Screen dimension constants */
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

/* points INFO */
const int XPOINTS = 8;
const int YPOINTS = 8;
const int POINTS_DISTANCE = 100;
const double INCLINATION = 0.7;
#endif