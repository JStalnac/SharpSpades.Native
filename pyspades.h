#pragma once

#include "common_c.h"
#include "vxl_c.h"

extern "C"
{
    int validate_hit(float shooter_x, float shooter_y, float shooter_z,
                 float orientation_x, float orientation_y, float orientation_z,
                 float ox, float oy, float oz,
                 float tolerance);
    long can_see(MapData *map, float x0, float y0, float z0, float x1, float y1,
             float z1);
    long cast_ray(MapData *map, float x0, float y0, float z0, float x1, float y1,
              float z1, float length, long *x, long *y, long *z);
    int cube_line(int x1, int y1, int z1, int x2, int y2, int z2,
        LongVector *cube_array);
    int try_uncrouch(PlayerType *p);
    long move_player(PlayerType *p);
    GrenadeType *create_grenade(Vector *p, Vector *v);
    int move_grenade(GrenadeType *g);
    PlayerType *create_player();
    void destroy_player(PlayerType *player);
    void destroy_grenade(GrenadeType *grenade);
    void set_globals(MapData *map, float time, float dt);
}
