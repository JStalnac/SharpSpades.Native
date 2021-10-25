#define FALL_SLOW_DOWN       0.24f
#define FALL_DAMAGE_VELOCITY 0.58f
#define FALL_DAMAGE_SCALAR   4096
#define SQRT                 0.70710678f

#include "sharpspades.h"

#include <math.h>

static inline int clipbox(Map* map, float x, float y, float z)
{
    int sz;

    if (x < 0 || x >= 512 || y < 0 || y >= 512)
        return 1;
    else if (z < 0)
        return 0;
    sz = (int) z;
    if (sz == 63)
        sz = 62;
    else if (sz >= 64)
        return 1;
    return mapvxl_issolid(map, (int) x, (int) y, sz);
}

// original C code

static inline void reposition_player(Player* p, Vector3f* position, float time)
{
    p->movement.eyePos = p->movement.position = *position;
    float f = p->lastclimb - time;
    if (f > -0.25f)
        p->movement.eyePos.z += (f + 0.25f) / 0.25f;
}

static inline void set_orientation_vectors(Vector3f* o, Vector3f* s, Vector3f* h)
{
    float f = sqrtf(o->x * o->x + o->y * o->y);
    s->x    = -o->y / f;
    s->y    = o->x / f;
    h->x    = -o->z * s->y;
    h->y    = o->z * s->x;
    h->z    = o->x * s->y - o->y * s->x;
}

void reorient_player(Player* p, Vector3f* orientation)
{
    p->movement.forwardOrientation = *orientation;
    set_orientation_vectors(orientation,
                            &p->movement.strafeOrientation,
                            &p->movement.heightOrientation);
}

int try_uncrouch(Map* map, Player* p)
{
    float x1 = p->movement.position.x + 0.45f;
    float x2 = p->movement.position.x - 0.45f;
    float y1 = p->movement.position.y + 0.45f;
    float y2 = p->movement.position.y - 0.45f;
    float z1 = p->movement.position.z + 2.25f;
    float z2 = p->movement.position.z - 1.35f;

    // first check if player can lower feet (in midair)
    if (p->airborne && !(clipbox(map, x1, y1, z1) || clipbox(map, x1, y2, z1) ||
                                               clipbox(map, x2, y1, z1) || clipbox(map, x2, y2, z1)))
        return (1);
    // then check if they can raise their head
    else if (!(clipbox(map, x1, y1, z2) || clipbox(map, x1, y2, z2) || clipbox(map, x2, y1, z2) ||
               clipbox(map, x2, y2, z2)))
    {
        p->movement.position.z -= 0.9f;
        p->movement.eyePos.z -= 0.9f;
        return (1);
    }
    return (0);
}

// player movement with autoclimb
void boxclipmove(Map* map, Player* p, float time, float delta)
{
    float offset, m, f, nx, ny, nz, z;
    long  climb = 0;

    f  = delta * 32.f;
    nx = f * p->movement.velocity.x + p->movement.position.x;
    ny = f * p->movement.velocity.y + p->movement.position.y;

    if (p->crouching) {
        offset = 0.45f;
        m      = 0.9f;
    } else {
        offset = 0.9f;
        m      = 1.35f;
    }

    nz = p->movement.position.z + offset;

    if (p->movement.velocity.x < 0)
        f = -0.45f;
    else
        f = 0.45f;
    z = m;
    while (z >= -1.36f && !clipbox(map, nx + f, p->movement.position.y - 0.45f, nz + z) &&
           !clipbox(map, nx + f, p->movement.position.y + 0.45f, nz + z))
        z -= 0.9f;
    if (z < -1.36f)
        p->movement.position.x = nx;
    else if (!p->crouching && p->movement.forwardOrientation.z < 0.5f &&
             !p->sprinting)
    {
        z = 0.35f;
        while (z >= -2.36f && !clipbox(map, nx + f, p->movement.position.y - 0.45f, nz + z) &&
               !clipbox(map, nx + f, p->movement.position.y + 0.45f, nz + z))
            z -= 0.9f;
        if (z < -2.36f) {
            p->movement.position.x = nx;
            climb = 1;
        } else
            p->movement.velocity.x = 0;
    } else
        p->movement.velocity.x = 0;

    if (p->movement.velocity.y < 0)
        f = -0.45f;
    else
        f = 0.45f;
    z = m;
    while (z >= -1.36f && !clipbox(map, p->movement.position.x - 0.45f, ny + f, nz + z) &&
           !clipbox(map, p->movement.position.x + 0.45f, ny + f, nz + z))
        z -= 0.9f;
    if (z < -1.36f)
        p->movement.position.y = ny;
    else if (!p->crouching && p->movement.forwardOrientation.z < 0.5f &&
             !p->sprinting && !climb)
    {
        z = 0.35f;
        while (z >= -2.36f && !clipbox(map, p->movement.position.x - 0.45f, ny + f, nz + z) &&
               !clipbox(map, p->movement.position.x + 0.45f, ny + f, nz + z))
            z -= 0.9f;
        if (z < -2.36f) {
            p->movement.position.y = ny;
            climb = 1;
        } else
            p->movement.velocity.y = 0;
    } else if (!climb)
        p->movement.velocity.y = 0;

    if (climb) {
        p->movement.velocity.x *= 0.5f;
        p->movement.velocity.y *= 0.5f;
        p->lastclimb = time;
        nz--;
        m = -1.35f;
    } else {
        if (p->movement.velocity.z < 0)
            m = -m;
        nz += p->movement.velocity.z * delta * 32.f;
    }

    p->airborne = 1;

    if (clipbox(map,
                p->movement.position.x - 0.45f,
                p->movement.position.y - 0.45f,
                nz + m) ||
        clipbox(map,
                p->movement.position.x - 0.45f,
                p->movement.position.y + 0.45f,
                nz + m) ||
        clipbox(map,
                p->movement.position.x + 0.45f,
                p->movement.position.y - 0.45f,
                nz + m) ||
        clipbox(map,
                p->movement.position.x + 0.45f,
                p->movement.position.y + 0.45f,
                nz + m))
    {
        if (p->movement.velocity.z >= 0) {
            p->wade     = p->movement.position.z > 61;
            p->airborne = 0;
        }
        p->movement.velocity.z = 0;
    } else
        p->movement.position.z = nz - offset;

    reposition_player(p, &p->movement.position, time);
}

long move_player(Map* map, Player* p, float time, float delta)
{
    float f, f2;

    // move player and perform simple physics (gravity, momentum, friction)
    if (p->jumping) {
        p->jumping             = 0;
        p->movement.velocity.z = -0.36f;
    }

    f = delta; // player acceleration scalar
    if (p->airborne)
        f *= 0.1f;
    else if (p->crouching)
        f *= 0.3f;
    else if ((p->secondary_fire && p->item == TOOL_GUN) ||
             p->sneaking)
        f *= 0.5f;
    else if (p->sprinting)
        f *= 1.3f;

    if ((p->movForward || p->movBackwards) &&
        (p->movLeft || p->movRight))
        f *= SQRT; // if strafe + forward/backwards then limit diagonal velocity

    if (p->movForward) {
        p->movement.velocity.x += p->movement.forwardOrientation.x * f;
        p->movement.velocity.y += p->movement.forwardOrientation.y * f;
    } else if (p->movBackwards) {
        p->movement.velocity.x -= p->movement.forwardOrientation.x * f;
        p->movement.velocity.y -= p->movement.forwardOrientation.y * f;
    }
    if (p->movLeft) {
        p->movement.velocity.x -= p->movement.strafeOrientation.x * f;
        p->movement.velocity.y -= p->movement.strafeOrientation.y * f;
    } else if (p->movRight) {
        p->movement.velocity.x += p->movement.strafeOrientation.x * f;
        p->movement.velocity.y += p->movement.strafeOrientation.y * f;
    }

    f = delta + 1;
    p->movement.velocity.z += delta;
    p->movement.velocity.z /= f; // air friction
    if (p->wade)
        f = delta * 6.f + 1; // water friction
    else if (!p->airborne)
        f = delta * 4.f + 1; // ground friction
    p->movement.velocity.x /= f;
    p->movement.velocity.y /= f;
    f2 = p->movement.velocity.z;
    boxclipmove(map, p, time, delta);
    // hit ground... check if hurt
    if (!p->movement.velocity.z && (f2 > FALL_SLOW_DOWN)) {
        // slow down on landing
        p->movement.velocity.x *= 0.5f;
        p->movement.velocity.y *= 0.5f;

        // return fall damage
        if (f2 > FALL_DAMAGE_VELOCITY) {
            f2 -= FALL_DAMAGE_VELOCITY;
            return ((long) (f2 * f2 * FALL_DAMAGE_SCALAR));
        }

        return (-1); // no fall damage but play fall sound
    }

    return (0); // no fall damage
}