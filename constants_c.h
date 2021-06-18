#ifndef CONSTANTS_C_H
#define CONSTANTS_C_H

// maximum .VXL dimensions in both x & y direction
#define VXL_MAX_SIZE 512
#define VXL_MAX_SIZEM (VXL_MAX_SIZE - 1)
#define VSIDSQ (VXL_MAX_SIZE * VXL_MAX_SIZE)

//Maximum .VXL dimensions in z direction (height)
#define MAXZDIM 64
#define FALL_SLOW_DOWN 0.24f
#define FALL_DAMAGE_VELOCITY 0.58f
#define FALL_DAMAGE_SCALAR 4096
#define WEAPON_PRIMARY 1

#define CUBE_ARRAY_LENGTH 64

#endif
