#ifndef WINDOW_H_INCLUDE
#define WINDOW_H_INCLUDE
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

typedef struct Window{
    GLFWwindow* handle;
    int width;
    int height;
    const char* title;
} Window;

Window* create_window(int width, int height, const char* title);
void close_window(Window* window);



#endif