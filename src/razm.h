#ifndef RAZM_H_INCLUDE
#define RAZM_H_INCLUDE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif


typedef struct vec3{
    float x; float y; float z;
} vec3;
typedef struct vec4{
    float x; float y; float z; float w;
} vec4;

typedef struct mat4x4{
    float data[4][4];
} mat4x4;

#define create_mat4x4(X) _Generic(X, float: create_mat4x4_float, vec4: create_mat4x4_vec4)(X)

mat4x4 create_mat4x4_float(float value);
mat4x4 create_mat4x4_vec4(vec4 axis);
vec4 multiply_mat4x4_vec4(mat4x4* matrix, vec4* vector);
mat4x4 multiply_mat4x4_mat4x4(mat4x4* a, mat4x4* b);
mat4x4 translate_mat4x4(mat4x4* matrix, vec3 translation);
mat4x4 scale_mat4x4(mat4x4* matrix, vec3 scale);
mat4x4 rotate_mat4x4(mat4x4* matrix, float a, vec3 axis);
float degree(float radians);
float radians(float degrees);

void print_mat4x4(mat4x4* matrix);
void print_vec4(vec4* vec);



#endif