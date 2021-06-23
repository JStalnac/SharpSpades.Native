#ifndef COMMON_C_H
#define COMMON_C_H

typedef struct 
{
    float x, y, z;
} Vector;

typedef struct 
{
    long x, y, z;
} LongVector;

typedef struct
{
    Vector f, s, h;
} Orientation;

typedef struct
{
    Vector p;
    Vector e;
    Vector v;
    Vector s;
    Vector h;
    Vector f;
    int mf, mb, ml, mr, jump, crouch, sneak, sprint, primary_fire,
        secondary_fire;
    float lastclimb;
    int airborne, wade, alive, weapon;
} Player;

typedef struct
{
    Vector p, v;
} Grenade;

#endif