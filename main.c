#include "terrain.h"

int main(void)
{
  SDL_Instance instance;

  instance.points3d = init_points3d();
  if (init_instance(&instance) != 0)
    return (1);

  while (1)
  {
    if (poll_events() == 1)
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
  draw3dpoints(instance, instance->points3d);
}

point3d_t **init_points3d(void)
{
  point3d_t **points3d = NULL;
  int i = 0, j = 0;
  int matris[3][2] = {
      {1, 2}, {4, 6}, {3, 7}};
  int heights[8][8] = {
      {120, 60, 40, 60, 20, -20, -80, -120},
      {40, 20, 30, 30, -10, -40, -90, -110},
      {20, 30, 10, 06, -6, -20, -26, -90},
      {0, -6, 10, 10, -6, -20, -20, -40},
      {-20, -20, -18, -14, -40, -20, -20, -30},
      {-10, -10, -10, -10, -8, -20, -20, -30},
      {20, 10, 10, 10, 10, 04, 10, -10},
      {30, 24, 24, 22, 20, 18, 14, 16}};

  points3d = malloc(sizeof(point3d_t *) * XPOINTS);
  if (points3d == NULL)
  {
    printf("points were not able to initialize\n");
    return (NULL);
  }
  for (i = 0; i < XPOINTS; i++)
  {
    points3d[i] = malloc(sizeof(point3d_t) * YPOINTS);
    if (points3d[i] == NULL)
    {
      printf("points were not able to initialize\n");
      for (i = i - 1; i >= 0; i--)
        free(points3d[i]);
      free(points3d);
      return (NULL);
    }
  }

  for (i = 0; i < XPOINTS; i++)
  {
    for (j = 0; j < YPOINTS; j++)
    {
      points3d[i][j].x = j * POINTS_DISTANCE;
      points3d[i][j].y = i * POINTS_DISTANCE;
      points3d[i][j].z = heights[i][j];
    }
  }
  return (points3d);
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
    for (j = 0; j < YPOINTS; j++)
    {
      x = INCLINATION * points[i][j].x - INCLINATION * points[i][j].y + SCREEN_WIDTH / 2;
      y = (1 - INCLINATION) * points[i][j].x + (1 - INCLINATION) * points[i][j].y - points[i][j].z + SCREEN_HEIGHT / 2;
      SDL_RenderDrawPoint(instance->renderer, x, y);
      //SDL_RenderDrawLine(instance->renderer, x_prev, y_prev, x, y);
      x_prev = x;
      y_prev = y;
      printf("Dibujar punto: x=%d   y=%d\n", x, y);
    }
  }
}

void TheExit(SDL_Instance *instance)
{
  free_points3d(instance->points3d);
  SDL_DestroyWindow(instance->window);
  SDL_DestroyRenderer(instance->renderer);
  SDL_Quit();
  exit(0);
}

int poll_events()
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
      break;
    default:
      break;
    }
  }
  return (0);
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
