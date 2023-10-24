#include "engine.h"


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

void run_engine(){
    Window* window = create_window(1200, 800, "raz");
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

    unsigned int triangle_shader = create_shader("E:\\GitRepos\\raz\\shaders\\triangle.vert", "E:\\GitRepos\\raz\\shaders\\triangle.frag");
    glUseProgram(triangle_shader);

    

    while (!glfwWindowShouldClose(window->handle))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
    close_window(window);
}