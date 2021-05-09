#include "terrain.h"

/**
 * main - Raise the terrain project, it shows a 3d terrain
 * The user is able to rotate the terrain and change the inclination
 * view using the arrow keys
 * 
 * Return: 0 if program is normally closed, 1 if an error occur
 * 
 */
int main(int argc, char **argv)
{
  SDL_Instance instance;

  instance.points3d = init_points3d(&instance);
  instance.points2d = init_points2d(&instance);
  instance.inclination = INCLINATION;

  if (init_instance(&instance) != 0)
    return (1);

  while (1)
  {
    if (poll_events(&instance) == 1)
      break;
    SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
    SDL_RenderClear(instance.renderer);

    draw_stuff(&instance);
    SDL_RenderPresent(instance.renderer); /* I think is to update canvas */
  }
  TheExit(&instance);
  return (0);
}

/**
 * TheExit - Function to free and destroy array of points windows and 
 * renderer used during the program
 * 
 * @instance: instance of variables
 * Return: nothing
 */
void TheExit(SDL_Instance *instance)
{
  free_points2d(instance->points2d);
  free_points3d(instance->points3d);
  SDL_DestroyWindow(instance->window);
  SDL_DestroyRenderer(instance->renderer);
  SDL_Quit();
  exit(0);
}

/**
 * poll_events - read the events created by the user, 
 * if the user press left or right arrow key the structure is rotared 
 * ROTATIONANGLE to the respective side
 * if the user press up or down arrow key the instance->inclination 
 * EXTRAINCLINATION is added or substracted
 * @instance: instance of variables
 * Return: if catched event is for exit the program returns 1,
 * otherwise returns 0
 */
int poll_events(SDL_Instance *instance)
{
  SDL_Event event;
  SDL_KeyboardEvent key;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      return (1);
    case SDL_KEYDOWN:
      key = event.key;
      /* if 'ESCAPE' is pressed */
      if (key.keysym.scancode == 0x29)
        return (1);
      if (key.keysym.sym == SDLK_LEFT)
        rotate_points(instance, ROTATIONANGLE);
      if (key.keysym.sym == SDLK_RIGHT)
        rotate_points(instance, -ROTATIONANGLE);
      if (key.keysym.sym == SDLK_UP)
        change_inclination(instance, -EXTRAINCLINATION);
      if (key.keysym.sym == SDLK_DOWN)
        change_inclination(instance, EXTRAINCLINATION);

      break;
    default:
      break;
    }
  }
  return (0);
}

/**
 * init_instance - initialize the windows, renderer and screenSurface from instance
 * @instance: instance of variables
 * Return: returns 0, unless an error occurs, in which case it returns 1
 */
int init_instance(SDL_Instance *instance)
{
  /* Initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    fprintf(stderr, "unable to initializa SDL: %s\n", SDL_GetError());
    return (1);
  }

  /* create a new window instance */
  instance->window = SDL_CreateWindow("Raise the terrain dude!!", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                      0);
  if (instance->window == NULL)
  {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return (1);
  }

  /* Create a new Renderer instance linked to the window */
  instance->renderer = SDL_CreateRenderer(instance->window, -1,
                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (instance->renderer == NULL)
  {
    SDL_DestroyWindow(instance->window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return (1);
  }

  instance->screenSurface = SDL_GetWindowSurface(instance->window);
  if (instance->screenSurface == NULL)
  {
    printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    TheExit(instance);
  }

  return (0);
}
