#ifndef TERRAINLIB

#define TERRAINLIB

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

typedef struct SDL_Instance
{
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer;
  struct point3d_t **points3d;
  struct point2d_t **points2d;
  double inclination;
} SDL_Instance;

typedef struct point3d_t
{
  double x;
  double y;
  double z;
} point3d_t;

typedef struct point2d_t
{
  double x;
  double y;
} point2d_t;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance *instance);
int poll_events(SDL_Instance *instance);
int getSurface(SDL_Surface **screenSurface, SDL_Instance *instance);
void TheExit(SDL_Instance *instance);
void rotate_points(SDL_Instance *instance, double angle);
void change_inclination(SDL_Instance *instance, double extra_inclination);

/* utils.c */
point3d_t **init_points3d(SDL_Instance *instance);
point2d_t **init_points2d(SDL_Instance *instance);
void free_points2d(point2d_t **points);
void free_points3d(point3d_t **points);
void draw3dpoints(SDL_Instance *instance, point3d_t **points);
void points3dto2d(SDL_Instance *instance);

/*  Screen dimension constants */
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

/* points INFO */
const int XPOINTS = 8;
const int YPOINTS = 8;
const int POINTS_DISTANCE = 100;
const double INCLINATION = 0.7;
#endif