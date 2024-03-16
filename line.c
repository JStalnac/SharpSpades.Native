/*
    Copyright (c) Mathias Kaerlev 2011-2012.
    Modified by DarkNeutrino and CircumScriptor

    Cobe based upon pyspades in file world_c.cpp
    hugely modified to fit this project.
*/

#include "sharpspades.h"

#include <stdlib.h>

#define TMAX_ALT_VALUE  (0x3FFFFFFF / 1024)
#define MAX_LINE_LENGTH 50

/**
 * @brief Calculate block line
 *
 * @param v1 Start position
 * @param v2 End position
 * @param result Array of blocks positions
 * @return Number of block positions
 */
int block_line(const vec3i* v1, const vec3i* v2, vec3i* result)
{
    int count = 0;

    vec3i pos  = *v1;
    vec3i dist = {v2->x - v1->x, v2->y - v1->y, v2->z - v1->z};
    vec3i step;
    vec3i a;
    vec3i tmax;
    vec3i delta;

    step.x = dist.x < 0 ? -1 : 1;
    step.y = dist.y < 0 ? -1 : 1;
    step.z = dist.z < 0 ? -1 : 1;

    a.x = abs(dist.x);
    a.y = abs(dist.y);
    a.z = abs(dist.z);

    if (a.x >= a.y && a.x >= a.z) {
        tmax.x = 512;
        tmax.y = a.y != 0 ? a.x * 512 / a.y : TMAX_ALT_VALUE;
        tmax.z = a.z != 0 ? a.x * 512 / a.z : TMAX_ALT_VALUE;
    } else if (a.y >= a.z) {
        tmax.x = a.x != 0 ? a.y * 512 / a.x : TMAX_ALT_VALUE;
        tmax.y = 512;
        tmax.z = a.z != 0 ? a.y * 512 / a.z : TMAX_ALT_VALUE;
    } else {
        tmax.x = a.x != 0 ? a.z * 512 / a.x : TMAX_ALT_VALUE;
        tmax.y = a.y != 0 ? a.z * 512 / a.y : TMAX_ALT_VALUE;
        tmax.z = 512;
    }

    delta.x = tmax.x * 2;
    delta.y = tmax.y * 2;
    delta.z = tmax.z * 2;

    while (1) {
        result[count++] = pos;

        if (count >= MAX_LINE_LENGTH || (pos.x == v2->x && pos.y == v2->y && pos.z == v2->z)) { // reached limit or end
            break;
        }

        if (tmax.z <= tmax.x && tmax.z <= tmax.y) {
            pos.z += step.z;
            if (pos.z >= 64) {
                break;
            }
            tmax.z += delta.z;
        } else if (tmax.x < tmax.y) {
            pos.x += step.x;
            if (pos.x >= 512) {
                break;
            }
            tmax.x += delta.x;
        } else {
            pos.y += step.y;
            if (pos.y >= 512) {
                break;
            }
            tmax.y += delta.y;
        }
    }

    return count;
}