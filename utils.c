#include "terrain.h"

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
            points3d[i][j].x = i * POINTS_DISTANCE;
            points3d[i][j].y = j * POINTS_DISTANCE;
            points3d[i][j].z = heights[i][j];
        }
    }
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
    int i = 0, j = 0, x, y;

    for (i = 0; i < XPOINTS; i++)
    {
        for (j = 0; j < YPOINTS; j++)
        {
            x = INCLINATION * points[i][j].x - INCLINATION * points[i][j].y;
            y = (1 - INCLINATION) * points[i][j].x + (1 - INCLINATION) * points[i][j].y - points[i][j].z;
            SDL_RenderDrawPoint(instance->renderer, x, y);
        }
    }
}
