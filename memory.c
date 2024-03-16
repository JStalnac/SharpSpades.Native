#include "sharpspades.h"

#include <stdlib.h>

Player* create_player()
{
    return (Player*)malloc(sizeof(Player));
}

void destroy_player(Player* p)
{
    free(p);
}

Grenade* create_grenade()
{
    return (Grenade*)malloc(sizeof(Grenade));
}

void destroy_grenade(Grenade* g)
{
    free(g);
}

MapVxl* create_map()
{
    return (MapVxl*)malloc(sizeof(MapVxl));
}

void destroy_map(MapVxl* m)
{
    free(m);
}