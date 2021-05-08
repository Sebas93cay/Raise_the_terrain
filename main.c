#include "terrain.h"

int main(void)
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

void draw_stuff(SDL_Instance *instance)
{
  /*  SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0XFF, 0XFF, 0XFF);
    SDL_RenderDrawLine(instance->renderer, 10, 10, 100, 100);
  SDL_SetRenderDrawColor(instance->renderer, 0x00, 0XFF, 0X00, 0XFF);
  SDL_RenderDrawPoint(instance->renderer, 150, 150);
 */
  SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0XFF, 0XFF, 0XFF);
  points3dto2d(instance);
  draw3dpoints(instance, instance->points3d);
}

point2d_t **init_points2d(SDL_Instance *instance)
{
  int i = 0;

  instance->points2d = malloc(sizeof(point2d_t *) * XPOINTS);
  if (instance->points2d == NULL)
  {
    printf("points were not able to initialize\n");
    return (NULL);
  }
  for (i = 0; i < XPOINTS; i++)
  {
    instance->points2d[i] = malloc(sizeof(point2d_t) * YPOINTS);
    if (instance->points2d[i] == NULL)
    {
      printf("points were not able to initialize\n");
      for (i = i - 1; i >= 0; i--)
        free(instance->points2d[i]);
      free(instance->points2d);
      return (NULL);
    }
  }
  return (instance->points2d);
}

void free_points2d(point2d_t **points)
{
  int i = 0;

  for (i = 0; i < XPOINTS; i++)
    free(points[i]);
  free(points);
}

void free_points3d(point3d_t **points)
{
  int i = 0;

  for (i = 0; i < XPOINTS; i++)
    free(points[i]);
  free(points);
}

void draw3dpoints(SDL_Instance *instance, point3d_t **points)
{
  int i = 0, j = 0, x = 0, y = 0, x_prev = 0, y_prev = 0;

  for (i = 0; i < XPOINTS; i++)
  {
    for (j = 0; j < YPOINTS - 1; j++)
    {
      SDL_RenderDrawLine(instance->renderer, instance->points2d[i][j].x,
                         instance->points2d[i][j].y,
                         instance->points2d[i][j + 1].x,
                         instance->points2d[i][j + 1].y);
    }
  }
  for (j = 0; j < YPOINTS; j++)
  {
    for (i = 0; i < XPOINTS - 1; i++)
    {
      SDL_RenderDrawLine(instance->renderer, instance->points2d[i][j].x,
                         instance->points2d[i][j].y,
                         instance->points2d[i + 1][j].x,
                         instance->points2d[i + 1][j].y);
    }
  }
}

void points3dto2d(SDL_Instance *instance)
{
  int i = 0, j = 0;
  point3d_t **points = instance->points3d;

  for (i = 0; i < XPOINTS; i++)
  {
    for (j = 0; j < YPOINTS; j++)
    {
      (instance->points2d)[i][j].x = instance->inclination * points[i][j].x - instance->inclination * points[i][j].y + SCREEN_WIDTH / 2;
      (instance->points2d)[i][j].y = (1 - instance->inclination) * points[i][j].x + (1 - instance->inclination) * points[i][j].y - points[i][j].z + SCREEN_HEIGHT / 2;
    }
  }
}

void change_inclination(SDL_Instance *instance, double extra_inclination)
{
  instance->inclination += extra_inclination;
}

void TheExit(SDL_Instance *instance)
{
  free_points2d(instance->points2d);
  free_points3d(instance->points3d);
  SDL_DestroyWindow(instance->window);
  SDL_DestroyRenderer(instance->renderer);
  SDL_Quit();
  exit(0);
}

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
        rotate_points(instance, 5);

      if (key.keysym.sym == SDLK_RIGHT)
        rotate_points(instance, -5);
      if (key.keysym.sym == SDLK_UP)
        change_inclination(instance, -0.01);
      if (key.keysym.sym == SDLK_DOWN)
        change_inclination(instance, 0.01);

      break;
    default:
      break;
    }
  }
  return (0);
}

void rotate_points(SDL_Instance *instance, double angle)
{
  double rads = 0, prevx, prevy;
  int i, j;

  rads = angle * M_PI / 180;

  for (i = 0; i < XPOINTS; i++)
  {
    for (j = 0; j < YPOINTS; j++)
    {
      prevx = instance->points3d[i][j].x;
      prevy = instance->points3d[i][j].y;
      instance->points3d[i][j].x = (prevx * cos(rads)) - (prevy * sin(rads));
      instance->points3d[i][j].y = (prevx * sin(rads)) + (prevy * cos(rads));
    }
  }
}

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
