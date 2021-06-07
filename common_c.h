// vi: set ft=cpp
#pragma once

class Vector
{
  public:
    float x, y, z;

    Vector()
    {
        x = 0.0, y = 0.0, z = 0.0;
    }
    Vector(float x, float y, float z)
        : x(x), y(y), z(z) {}
    void set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct LongVector
{
    long x, y, z;
};

struct Orientation
{
    Vector f, s, h;
};

struct PlayerType
{
    Vector p, e, v, s, h, f;
    int mf, mb, ml, mr, jump, crouch, sneak, sprint, primary_fire,
        secondary_fire;
    float lastclimb;
    int airborne, wade, alive, weapon;
};

struct GrenadeType
{
    Vector p, v;
};
