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
#define normlize_vector(X) _Generic(X, vec3: normlize_vec3, vec4: normlize_vec4)(X);
#define magnitude_vector(X) _Generic(X, vec3: magnitude_vec3, vec4: magnitude_vec4)(X);

mat4x4 create_mat4x4_float(float value);
mat4x4 create_mat4x4_vec4(vec4 axis);
mat4x4 create_mat4x4_floats(float x1, float x2, float x3, float x4,
                            float y1, float y2, float y3, float y4,
                            float z1, float z2, float z3, float z4,
                            float w1, float w2, float w3, float w4);
mat4x4 prespective_matrix(float aspect, float fov, float far, float near);
mat4x4 look_at(vec3 pos, vec3 target, vec3 up);


float magnitude_vec3(vec3 vector);
float magnitude_vec4(vec4 vector);
float dot_vec3(vec3 a, vec3 b);
vec3 add_vec3(vec3 a, vec3 b);
vec3 sub_vec3(vec3 a, vec3 b);
vec3 multiply_vec3(vec3 a, float s);
vec3 cross_vec3(vec3 a, vec3 b);
vec3 normlize_vec3(vec3 vector);
vec4 add_vec4(vec4 a, vec4 b);
vec4 sub_vec4(vec4 a, vec4 b);
vec4 normlize_vec4(vec4 vector);
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