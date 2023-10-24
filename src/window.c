#include "window.h"

Window* create_window(int width, int height, const char* title){
    Window* window = malloc(sizeof(Window));
    if (!glfwInit()){
        printf("glfw Failed to initialize\n");
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window->width = width;
    window->height = height;
    window->title = title;
    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window->handle)
    {
        glfwTerminate();
        printf("glfw failed to create a window\n");
        exit(-1);
    }

    glfwMakeContextCurrent(window->handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Raz Failed to initialize GLAD\n");
        exit(-1);
    }
    return window;
}

void close_window(Window* window){
    glfwDestroyWindow(window->handle);
    glfwTerminate();
    free(window);
    printf("engine terminated\n");
}