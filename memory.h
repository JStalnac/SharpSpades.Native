#include <stdlib.h>

#include "common_c.h"
#include "libvxl.h"

Player *create_player()
{
    Player *player = (Player*)malloc(sizeof(Player));
    player->s.x = 0;
    player->s.y = 1;
    player->s.z = 0;
    player->h.x = 0;
    player->h.y = 0;
    player->h.z = 1;
    player->f.x = 1;
    player->f.y = 0;
    player->f.z = 0;
    player->p.x = 0;
    player->p.y = 0;
    player->p.z = 0.0f;
    player->e = player->p;
    player->v.x = player->v.y = player->v.z = 0;
    player->mf = player->mb = player->ml = player->mr = player->jump =
        player->crouch = player->sneak = 0;
    player->airborne = player->wade = 0;
    player->lastclimb = 0;
    player->alive = 1;
    return player;
}

void destroy_player(Player *player)
{
    free(player);
}


Grenade *create_grenade(Vector *position, Vector *velocity)
{
    Grenade *g = (Grenade*)malloc(sizeof(Grenade));
    g->p = *position;
    g->v = *velocity;
    return g;
}

void destroy_grenade(Grenade *grenade)
{
    free(grenade);
}

struct libvxl_map *create_map()
{
    return (struct libvxl_map*)malloc(sizeof(struct libvxl_map));
}

void destroy_map(struct libvxl_map *map)
{
    free(map);
}