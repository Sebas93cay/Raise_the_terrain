#include "terrain.h"

point3d_t **init_points3d(SDL_Instance *instance)
{
    int i = 0, j = 0, offset_tomid = 0;
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

    instance->points3d = malloc(sizeof(point3d_t *) * XPOINTS);
    if (instance->points3d == NULL)
    {
        printf("points were not able to initialize\n");
        return (NULL);
    }
    for (i = 0; i < XPOINTS; i++)
    {
        (instance->points3d)[i] = malloc(sizeof(point3d_t) * YPOINTS);
        if ((instance->points3d)[i] == NULL)
        {
            printf("points were not able to initialize\n");
            for (i = i - 1; i >= 0; i--)
                free((instance->points3d)[i]);
            free((instance->points3d)[i]);
            return (NULL);
        }
    }

    offset_tomid = POINTS_DISTANCE * (XPOINTS - 1) / 2;
    for (i = 0; i < XPOINTS; i++)
    {
        for (j = 0; j < YPOINTS; j++)
        {
            (instance->points3d)[i][j].x = j * POINTS_DISTANCE - offset_tomid;
            (instance->points3d)[i][j].y = i * POINTS_DISTANCE - offset_tomid;
            (instance->points3d)[i][j].z = heights[i][j];
        }
    }

    return (instance->points3d);
}

/**
 * rotate_points - rotate instance->points3d angle degrees
 * @instance: instance of variables
 * @angle: angle to rotate the points
 * Return: nothing
 */
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

/**
 * change_inclination - add extra_inclination to instance->inclination 
 *
 * @instance: instance of variables
 * @extra_inclination: inclination to add to instance->inclination
 * Return: nothing
 */
void change_inclination(SDL_Instance *instance, double extra_inclination)
{
    instance->inclination += extra_inclination;
}

/**
 * points3dto2d - transform points from instance->points3d to 2dpoints
 * to print in windows
 *
 * @instance: instance of variables 
 * Return: nothing
 */
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

/**
 * drawstructure - draw to structure
 * @instance: instance of variables 
 * Return: nothing
 */
void drawstructure(SDL_Instance *instance)
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

/**
 * draw_stuff - draw the structure
 * @instance: instance of variables 
 * Return: nothing
 */
void draw_stuff(SDL_Instance *instance)
{
    SDL_SetRenderDrawColor(instance->renderer, 0xFF, 0XFF, 0XFF, 0XFF);
    points3dto2d(instance);
    drawstructure(instance);
}

/**
 * init_points2d - allocate memory space for array of arrays for 2dpoints
 * @instance: instance of variables 
 * Return: nothing
 */
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

/**
 * free_points2d - free spaces used for 2d points
 * @instance: instance of variables 
 * Return: nothing
 */
void free_points2d(point2d_t **points)
{
    int i = 0;

    for (i = 0; i < XPOINTS; i++)
        free(points[i]);
    free(points);
}

/**
 * free_points3d - free spaces used for 3d points
 * @instance: instance of variables 
 * Return: nothing
 */
void free_points3d(point3d_t **points)
{
    int i = 0;

    for (i = 0; i < XPOINTS; i++)
        free(points[i]);
    free(points);
}
