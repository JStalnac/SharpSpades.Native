#ifndef LIBMAPVXL_H
#define LIBMAPVXL_H

#include <stddef.h>

#define MAP_X_MAX 512
#define MAP_Y_MAX MAP_X_MAX
#define MAP_Z_MAX 64
#define DEFAULT_COLOR 0xFF674028

typedef struct {
    unsigned char blocks[MAP_X_MAX][MAP_Y_MAX][MAP_Z_MAX];
    unsigned int color[MAP_X_MAX][MAP_Y_MAX][MAP_Z_MAX];
} MapVxl;

void mapvxl_readmap(MapVxl *map, unsigned char *v);
size_t mapvxl_writemap(MapVxl *map, unsigned char *mapOut);
unsigned char mapvxl_issurface(MapVxl *map, int x, int y, int z);
unsigned char mapvxl_issolid(MapVxl *map, int x, int y, int z);
void mapvxl_setcolor(MapVxl *map, int x, int y, int z, unsigned int c);
void mapvxl_setair(MapVxl *map, int x, int y, int z);
unsigned int mapvxl_getcolor(MapVxl *map, int x, int y, int z);

#endif
