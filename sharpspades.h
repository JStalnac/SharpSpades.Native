#ifndef SHARPSPADES_H
#define SHARPSPADES_H

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif
    #include "libmapvxl.h"
    int block_line(const vec3i* v1, const vec3i* v2, vec3i* result);

    Player* create_player();
    void destroy_player(Player* p);
    Grenade* create_grenade();
    void destroy_grenade(Grenade* g);
    MapVxl* create_map();
    void destroy_map(MapVxl* m);

    int validate_hit(Vector3f shooter,
                 Vector3f orientation,
                 Vector3f other,
                 float tolerance);
    long can_see(MapVxl* map, float x0, float y0, float z0, float x1, float y1,
             float z1);
    long cast_ray(MapVxl* map, float x0, float y0, float z0, float x1, float y1,
              float z1, float length, long *x, long *y, long *z);
    
    int try_uncrouch(MapVxl* map, Player *p);
    long move_player(MapVxl* map, Player* p, float delta, float time);
    
    int move_grenade(MapVxl* map, Grenade* g, float delta);
#ifdef __cplusplus
}
#endif
#endif // SHARPSPADES_H