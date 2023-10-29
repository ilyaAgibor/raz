#ifndef CAMERA_H_INCLUDE
#define CAMERA_H_INCLUDE
#include "razm.h"

typedef struct Camera{
    vec3 position;
    vec3 direction; //same as forward
    vec3 up;
    vec3 right;
} Camera;



#endif