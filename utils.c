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
