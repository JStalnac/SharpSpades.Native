#ifndef TYPES_H
#define TYPES_H

#include "libmapvxl.h"

typedef MapVxl Map;

typedef enum {
    TOOL_SPADE   = 0,
    TOOL_BLOCK   = 1,
    TOOL_GUN     = 2,
    TOOL_GRENADE = 3,
} Tool;

typedef struct
{
    int x;
    int y;
    int z;
} vec3i;

typedef struct
{
    float x;
    float y;
    float z;
} Vector3f;

typedef struct
{
    long x;
    long y;
    long z;
} Vector3l;

typedef struct
{
    Vector3f position;
    Vector3f eyePos;
    Vector3f velocity;
    Vector3f strafeOrientation;
    Vector3f heightOrientation;
    Vector3f forwardOrientation;
    Vector3f previousOrientation;
} Movement;

typedef struct
{
    Tool item;
    char movForward;
    char movBackwards;
    char movLeft;
    char movRight;
    char jumping;
    char crouching;
    char sneaking;
    char sprinting;
    char primary_fire;
    char secondary_fire;

    Movement movement;
    char    airborne;
    char    wade;
    float    lastclimb;
} Player;

typedef struct
{
    Vector3f position;
    Vector3f velocity;
} Grenade;

#endif