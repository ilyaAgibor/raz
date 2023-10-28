#include "razm.h"

float degree(float radians){
    return radians * (180.0f / M_PI);
}

float radians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

mat4x4 create_mat4x4_float(float value){
    mat4x4 matrix = {0};
    for(int i = 0; i < 4; i++)
        matrix.data[i][i] = value;
    return matrix;
}

mat4x4 create_mat4x4_vec4(vec4 axis){
    mat4x4 matrix = {0};
    matrix.data[0][0] = axis.x;
    matrix.data[1][1] = axis.y;
    matrix.data[2][2] = axis.z;
    matrix.data[3][3] = axis.w;
    return matrix;
}

mat4x4 create_mat4x4_vectors(vec4 i, vec4 j, vec4 k, vec4 e){
    mat4x4 matrix = {0};
    vec4 axises[4] = {i, j, k, e};
    for(int axis = 0; axis < 4; axis++){
        matrix.data[axis][0] = axises[axis].x;
        matrix.data[axis][1] = axises[axis].y;
        matrix.data[axis][2] = axises[axis].z;
        matrix.data[axis][3] = axises[axis].w;
    }
    return matrix;
}

mat4x4 create_mat4x4_floats(float x1, float x2, float x3, float x4,
                            float y1, float y2, float y3, float y4,
                            float z1, float z2, float z3, float z4,
                            float w1, float w2, float w3, float w4){
    return (mat4x4){x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4, w1, w2, w3, w4};
}
mat4x4 prespective_matrix(float aspect, float fov, float near, float far){
    float f = 1/(tanf(radians(fov/2.0f)));
    mat4x4 prespective = create_mat4x4_floats(
        aspect*f, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (far)/(far-near), -(far*near)/(far-near),
        0.0f, 0.0f, 1.0f, 0.0f
    );
    return prespective;
}

float magnitude_vec3(vec3* vector){
    return (float)sqrt(vector->x*vector->x + vector->y * vector->y + vector->z*vector->z);
}
float magnitude_vec4(vec4* vector){
    return (float)sqrt(vector->x*vector->x + vector->y * vector->y + vector->z*vector->z + vector->w * vector->w);
}

vec3 normlize_vec3(vec3* vector){
    float mag = magnitude_vec3(vector);
    return (vec3){vector->x/mag, vector->y/mag, vector->z/mag};
}
vec4 normlize_vec4(vec4* vector){
    float mag = magnitude_vec4(vector);
    return (vec4){vector->x/mag, vector->y/mag, vector->z/mag, vector->w/mag};
}

mat4x4 multiply_mat4x4_mat4x4(mat4x4* a, mat4x4* b){
    mat4x4 result = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < 4; k++) {
                result.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

mat4x4 translate_mat4x4(mat4x4* matrix, vec3 translation){
    mat4x4 result = *matrix;
    result.data[0][3] += translation.x;
    result.data[1][3] += translation.y;
    result.data[2][3] += translation.z;
    return result;
}
mat4x4 scale_mat4x4(mat4x4* matrix, vec3 scale){
    mat4x4 result = *matrix;
    result.data[0][0] = scale.x;
    result.data[1][1] = scale.y;
    result.data[2][2] = scale.z;
    return result;
}

mat4x4 rotate_mat4x4(mat4x4* matrix, float a, vec3 axis_vector){
    vec3 axis = normlize_vec3(&axis_vector);
    mat4x4 rotation_matrix = {0};
    rotation_matrix.data[3][3] = 1.0f;

    float cos_a = cos(a);
    float sin_a = sin(a);

    rotation_matrix.data[0][0] = cos_a + axis.x * axis.x * (1 - cos_a);
    rotation_matrix.data[0][1] = axis.x * axis.y * (1 - cos_a) - axis.z * sin_a;
    rotation_matrix.data[0][2] = axis.x * axis.z * (1 - cos_a) + axis.y * sin_a;

    rotation_matrix.data[1][0] = axis.y * axis.x * (1 - cos_a) + axis.z * sin_a;
    rotation_matrix.data[1][1] = cos_a + axis.y * axis.y * (1 - cos_a);
    rotation_matrix.data[1][2] = axis.y * axis.z * (1 - cos_a) - axis.x * sin_a;

    rotation_matrix.data[2][0] = axis.z * axis.x * (1 - cos_a) - axis.y * sin_a;
    rotation_matrix.data[2][1] = axis.z * axis.y * (1 - cos_a) + axis.x * sin_a;
    rotation_matrix.data[2][2] = cos_a + axis.z * axis.z * (1 - cos_a);

    mat4x4 result = multiply_mat4x4_mat4x4(&rotation_matrix, matrix);
    return result;
}



void print_mat4x4(mat4x4* matrix){
    printf("%c\t\t\t%c\n", 201, 187);
    printf("%c %.2f %.2f %.2f %.2f   %c\n", 186, matrix->data[0][0], matrix->data[0][1], matrix->data[0][2], matrix->data[0][3], 186);
    printf("%c %.2f %.2f %.2f %.2f   %c\n", 186, matrix->data[1][0], matrix->data[1][1], matrix->data[1][2], matrix->data[1][3], 186);
    printf("%c %.2f %.2f %.2f %.2f   %c\n", 186, matrix->data[2][0], matrix->data[2][1], matrix->data[2][2], matrix->data[2][3], 186);
    printf("%c %.2f %.2f %.2f %.2f   %c\n", 186, matrix->data[3][0], matrix->data[3][1], matrix->data[3][2], matrix->data[3][3], 186);
    printf("%c\t\t\t%c\n", 200, 188);
}

void print_vec4(vec4* vec){
    printf("[ %f %f %f %f ]\n", vec->x, vec->y, vec->z, vec->w);
}