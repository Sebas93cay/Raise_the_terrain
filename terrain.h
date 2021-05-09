#ifndef TERRAINLIB

#define TERRAINLIB

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

/**
 * SDL_Instance - instance of variables needed for the execution 
 * of the problem
 * @window: windows
 * @screenSurface: screensurface for the windows
 * @renderer: renderer
 * @points3d: array of arrays of points in 3d
 * @points2d: array of arrays of points in 3d represented in 2d
 * @inclination: inclination for view
 **/
typedef struct SDL_Instance
{
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Renderer *renderer;
  struct point3d_t **points3d;
  struct point2d_t **points2d;
  double inclination;
} SDL_Instance;

/**
 * point3d_t - representation of point in 3d
 * @x: x coordinate
 * @y: y coordinate
 * @z: z coordinate
 **/
typedef struct point3d_t
{
  double x;
  double y;
  double z;
} point3d_t;

/**
 * point3d_t - representation of point in 2d to print
 * in windows
 * @x: x coordinate
 * @y: y coordinate
 **/
typedef struct point2d_t
{
  double x;
  double y;
} point2d_t;

int init_instance(SDL_Instance *);
int poll_events(SDL_Instance *instance);
int getSurface(SDL_Surface **screenSurface, SDL_Instance *instance);
void TheExit(SDL_Instance *instance);

/* utils.c */
void rotate_points(SDL_Instance *instance, double angle);
void change_inclination(SDL_Instance *instance, double extra_inclination);
void draw_stuff(SDL_Instance *instance);
point3d_t **init_points3d(SDL_Instance *instance);
point2d_t **init_points2d(SDL_Instance *instance);
void free_points2d(point2d_t **points);
void free_points3d(point3d_t **points);
void drawstructure(SDL_Instance *instance);
void points3dto2d(SDL_Instance *instance);

/*  Screen dimension constants */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

/* points INFO */
#define XPOINTS 8
#define YPOINTS 8
#define POINTS_DISTANCE 100
#define INCLINATION 0.7
#define ROTATIONANGLE 5
#define EXTRAINCLINATION 0.01
#endif