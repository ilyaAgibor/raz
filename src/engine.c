#include "engine.h"

void run_engine(){
    Window* window = create_window(1200, 800, "raz");
    while (!glfwWindowShouldClose(window->handle))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
    close_window(window);
}