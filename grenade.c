#include "sharpspades.h"

#include <math.h>

static inline long clipworld(Map* map, long x, long y, long z)
{
    int sz;

    if (x < 0 || x >= 512 || y < 0 || y >= 512)
        return 0;
    if (z < 0)
        return 0;
    sz = (int) z;
    if (sz == 63)
        sz = 62;
    else if (sz >= 63)
        return 1;
    else if (sz < 0)
        return 0;
    return mapvxl_issolid(map, (int) x, (int) y, sz);
}

// returns 1 if there was a collision, 2 if sound should be played
int move_grenade(Map* map, Grenade* g, float delta)
{
    Vector3f fpos = g->position; // old position
    // do velocity & gravity (friction is negligible)
    float f = delta * 32;
    g->velocity.z += delta;
    g->position.x +=
    g->velocity.x * f;
    g->position.y +=
    g->velocity.y * f;
    g->position.z +=
    g->velocity.z * f;
    // do rotation
    // FIX ME: Loses orientation after 45 degree bounce off wall
    //  if(g->v.x > 0.1f || g->v.x < -0.1f || g->v.y > 0.1f || g->v.y < -0.1f)
    //  {
    //  f *= -0.5;
    // }
    // make it bounce (accurate)
    Vector3l lp;
    lp.x = (long) floor(g->position.x);
    lp.y = (long) floor(g->position.y);
    lp.z = (long) floor(g->position.z);

    int ret = 0;

    if (clipworld(map, lp.x, lp.y, lp.z)) // hit a wall
    {
#define BOUNCE_SOUND_THRESHOLD 0.1f

        ret = 1;
        if (fabs(g->velocity.x) > BOUNCE_SOUND_THRESHOLD ||
            fabs(g->velocity.y) > BOUNCE_SOUND_THRESHOLD ||
            fabs(g->velocity.z) > BOUNCE_SOUND_THRESHOLD)
            ret = 2; // play sound

        Vector3l lp2;
        lp2.x = (long) floor(fpos.x);
        lp2.y = (long) floor(fpos.y);
        lp2.z = (long) floor(fpos.z);
        if (lp.z != lp2.z && ((lp.x == lp2.x && lp.y == lp2.y) || !clipworld(map, lp.x, lp.y, lp2.z)))
            g->velocity.z =
            -g->velocity.z;
        else if (lp.x != lp2.x && ((lp.y == lp2.y && lp.z == lp2.z) || !clipworld(map, lp2.x, lp.y, lp.z)))
            g->velocity.x =
            -g->velocity.x;
        else if (lp.y != lp2.y && ((lp.x == lp2.x && lp.z == lp2.z) || !clipworld(map, lp.x, lp2.y, lp.z)))
            g->velocity.y =
            -g->velocity.y;
        g->position = fpos; // set back to old position
        g->velocity.x *= 0.36f;
        g->velocity.y *= 0.36f;
        g->velocity.z *= 0.36f;
    }
    return ret;
}