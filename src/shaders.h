#ifndef SHADERS_H_INCLUDE
#define SHADERS_H_INCLUDE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glad/glad.h>

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

typedef struct Shader{
    unsigned int id;
    struct UniformNote* head;
}Shader;

typedef struct UniformCach{     //136 bytes
    char name[128];
    int id;
}UniformCach;

typedef struct UniformNote{
    struct UniformNote* next;
    struct UniformCach* cach;
}UniformNote;


Shader create_shader(const char* vert, const char* frag);
void delete_shader(Shader* shader);

void set_uniform_bool(Shader* shader, const char* name, bool value);
void set_uniform_int(Shader* shader, const char* name, int value);
void set_uniform_float(Shader* shader, const char* name, float value);
void set_uniform_vec2(Shader* shader, const char* name, float x, float y);
void set_uniform_vec3(Shader* shader, const char* name, float x, float y, float z);
void set_uniform_vec4(Shader* shader, const char* name, float x, float y, float z, float w);



#endif