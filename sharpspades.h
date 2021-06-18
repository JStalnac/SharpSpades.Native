#include "common_c.h"

#ifdef __cplusplus
extern "C"
{
#endif
    #include "libvxl.h"
    #include "memory.h"

    int validate_hit(float shooter_x, float shooter_y, float shooter_z,
                 float orientation_x, float orientation_y, float orientation_z,
                 float ox, float oy, float oz,
                 float tolerance);
    long can_see(struct libvxl_map *map, float x0, float y0, float z0, float x1, float y1,
             float z1);
    long cast_ray(struct libvxl_map *map, float x0, float y0, float z0, float x1, float y1,
              float z1, float length, long *x, long *y, long *z);
    int cube_line(int x1, int y1, int z1, int x2, int y2, int z2,
        LongVector *cube_array);
    int try_uncrouch(struct libvxl_map *map, PlayerType *p);
    long move_player(struct libvxl_map *map, PlayerType *p, float delta, float time);
    int move_grenade(struct libvxl_map *map, Grenade *g, float delta);
#ifdef __cplusplus
}
#endif