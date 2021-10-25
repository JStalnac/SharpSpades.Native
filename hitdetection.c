#define VSID                 512 // maximum .VXL dimensions in both x & y direction
#define VSIDM                (VSID - 1)

#include "libmapvxl.h"
#include "sharpspades.h"
#include "types.h"

#include <math.h>

struct Orientation
{
    Vector3f forward;
    Vector3f strafe;
    Vector3f height;
};

static inline void get_orientation(struct Orientation* o, float orientation_x, float orientation_y, float orientation_z)
{
    float f;
    o->forward.x = orientation_x;
    o->forward.y = orientation_y;
    o->forward.z = orientation_z;
    f            = sqrtf(orientation_x * orientation_x + orientation_y * orientation_y);
    o->strafe.x  = -orientation_y / f;
    o->strafe.y  = orientation_x / f;
    o->strafe.z  = 0.0f;
    o->height.x  = -orientation_z * o->strafe.y;
    o->height.y  = orientation_z * o->strafe.x;
    o->height.z  = orientation_x * o->strafe.y - orientation_y * o->strafe.x;
}

int validate_hit(Vector3f shooter, Vector3f orientation, Vector3f other, float tolerance)
{
    float       cx, cy, cz, r, x, y;
    struct Orientation o;
    get_orientation(&o, orientation.x, orientation.y, orientation.z);
    other.x -= shooter.x;
    other.y -= shooter.y;
    other.z -= shooter.z;
    cz = other.x * o.forward.x + other.y * o.forward.y + other.z * o.forward.z;
    r  = 1.f / cz;
    cx = other.x * o.strafe.x + other.y * o.strafe.y + other.z * o.strafe.z;
    x  = cx * r;
    cy = other.x * o.height.x + other.y * o.height.y + other.z * o.height.z;
    y  = cy * r;
    r *= tolerance;
    int ret = (x - r < 0 && x + r > 0 && y - r < 0 && y + r > 0);
    return ret;
}

// silly VOXLAP function
static inline void ftol(float f, long* a)
{
    *a = (long) f;
}

static inline long isvoxelsolidwrap(Map* map, long x, long y, long z)
{
    if (z < 0)
        return 0;
    else if (z >= 64)
        return 1;
    return mapvxl_issolid(map, (int) x & VSIDM, (int) y & VSIDM, z);
}

long can_see(Map* map, float x0, float y0, float z0, float x1, float y1, float z1)
{
    Vector3f f, g;
    Vector3l a, c, d, p, i;
    d.x      = 0;
    d.y      = 0;
    d.z      = 0;
    long cnt = 0;

    ftol(x0 - .5f, &a.x);
    ftol(y0 - .5f, &a.y);
    ftol(z0 - .5f, &a.z);
    ftol(x1 - .5f, &c.x);
    ftol(y1 - .5f, &c.y);
    ftol(z1 - .5f, &c.z);

    if (c.x < a.x) {
        d.x = -1;
        f.x = x0 - a.x;
        g.x = (x0 - x1) * 1024;
        cnt += a.x - c.x;
    } else if (c.x != a.x) {
        d.x = 1;
        f.x = a.x + 1 - x0;
        g.x = (x1 - x0) * 1024;
        cnt += c.x - a.x;
    } else
        f.x = g.x = 0;
    if (c.y < a.y) {
        d.y = -1;
        f.y = y0 - a.y;
        g.y = (y0 - y1) * 1024;
        cnt += a.y - c.y;
    } else if (c.y != a.y) {
        d.y = 1;
        f.y = a.y + 1 - y0;
        g.y = (y1 - y0) * 1024;
        cnt += c.y - a.y;
    } else
        f.y = g.y = 0;
    if (c.z < a.z) {
        d.z = -1;
        f.z = z0 - a.z;
        g.z = (z0 - z1) * 1024;
        cnt += a.z - c.z;
    } else if (c.z != a.z) {
        d.z = 1;
        f.z = a.z + 1 - z0;
        g.z = (z1 - z0) * 1024;
        cnt += c.z - a.z;
    } else
        f.z = g.z = 0;

    ftol(f.x * g.z - f.z * g.x, &p.x);
    ftol(g.x, &i.x);
    ftol(f.y * g.z - f.z * g.y, &p.y);
    ftol(g.y, &i.y);
    ftol(f.y * g.x - f.x * g.y, &p.z);
    ftol(g.z, &i.z);

    if (cnt > 32)
        cnt = 32;
    while (cnt) {
        if (((p.x | p.y) >= 0) && (a.z != c.z)) {
            a.z += d.z;
            p.x -= i.x;
            p.y -= i.y;
        } else if ((p.z >= 0) && (a.x != c.x)) {
            a.x += d.x;
            p.x += i.z;
            p.z -= i.y;
        } else {
            a.y += d.y;
            p.y += i.z;
            p.z += i.x;
        }

        if (isvoxelsolidwrap(map, a.x, a.y, a.z))
            return 0;
        cnt--;
    }
    return 1;
}

long cast_ray(Map* map,
              float   x0,
              float   y0,
              float   z0,
              float   x1,
              float   y1,
              float   z1,
              float   length,
              long*   x,
              long*   y,
              long*   z)
{
    x1 = x0 + x1 * length;
    y1 = y0 + y1 * length;
    z1 = z0 + z1 * length;
    Vector3f f, g;
    Vector3l a, c, d, p, i;
    d.x      = 0;
    d.y      = 0;
    d.z      = 0;
    long cnt = 0;

    ftol(x0 - .5f, &a.x);
    ftol(y0 - .5f, &a.y);
    ftol(z0 - .5f, &a.z);
    ftol(x1 - .5f, &c.x);
    ftol(y1 - .5f, &c.y);
    ftol(z1 - .5f, &c.z);

    if (c.x < a.x) {
        d.x = -1;
        f.x = x0 - a.x;
        g.x = (x0 - x1) * 1024;
        cnt += a.x - c.x;
    } else if (c.x != a.x) {
        d.x = 1;
        f.x = a.x + 1 - x0;
        g.x = (x1 - x0) * 1024;
        cnt += c.x - a.x;
    } else
        f.x = g.x = 0;
    if (c.y < a.y) {
        d.y = -1;
        f.y = y0 - a.y;
        g.y = (y0 - y1) * 1024;
        cnt += a.y - c.y;
    } else if (c.y != a.y) {
        d.y = 1;
        f.y = a.y + 1 - y0;
        g.y = (y1 - y0) * 1024;
        cnt += c.y - a.y;
    } else
        f.y = g.y = 0;
    if (c.z < a.z) {
        d.z = -1;
        f.z = z0 - a.z;
        g.z = (z0 - z1) * 1024;
        cnt += a.z - c.z;
    } else if (c.z != a.z) {
        d.z = 1;
        f.z = a.z + 1 - z0;
        g.z = (z1 - z0) * 1024;
        cnt += c.z - a.z;
    } else
        f.z = g.z = 0;

    ftol(f.x * g.z - f.z * g.x, &p.x);
    ftol(g.x, &i.x);
    ftol(f.y * g.z - f.z * g.y, &p.y);
    ftol(g.y, &i.y);
    ftol(f.y * g.x - f.x * g.y, &p.z);
    ftol(g.z, &i.z);

    if (cnt > length)
        cnt = (long) length;
    while (cnt) {
        if (((p.x | p.y) >= 0) && (a.z != c.z)) {
            a.z += d.z;
            p.x -= i.x;
            p.y -= i.y;
        } else if ((p.z >= 0) && (a.x != c.x)) {
            a.x += d.x;
            p.x += i.z;
            p.z -= i.y;
        } else {
            a.y += d.y;
            p.y += i.z;
            p.z += i.x;
        }

        if (isvoxelsolidwrap(map, a.x, a.y, a.z)) {
            *x = a.x;
            *y = a.y;
            *z = a.z;
            return 1;
        }
        cnt--;
    }
    return 0;
}