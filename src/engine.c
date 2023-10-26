#include "engine.h"


float vertices[] = {
     0.5f, -0.9f, 0.0f,  // bottom right
    -0.5f, -0.9f, 0.0f,  // bottom left
    -0.5f,  0.9f, 0.0f,   // top left
    0.5f, 0.9f, 0.0f      //top right

};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    2, 0, 3
};  

void run_engine(){
    clock_t t = clock();
    Window* window = create_window(1200, 800, "raz");
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    Shader triangle_shader = create_shader("E:\\GitRepos\\raz\\shaders\\triangle.vert", "E:\\GitRepos\\raz\\shaders\\triangle.frag");    
    glUseProgram(triangle_shader.id);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mat4x4 trans = create_mat4x4(1.0f);
    //trans = translate_mat4x4(&trans, (vec3){0.5,0.5f,0.0f});
    //trans = rotate_mat4x4(&trans, radians(90), (vec3){0.0f,0.0f,1.0f});
    set_uniform_mat4x4(&triangle_shader, "trans", &trans);
    trans = scale_mat4x4(&trans, (vec3){1.0f, 1.0f, 1.0f});
   

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("The main loop started after %f seconds\n", time_taken);
    while (!glfwWindowShouldClose(window->handle))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(triangle_shader.id);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window->handle);
        glfwPollEvents();
    }
    delete_shader(&triangle_shader);
    close_window(window);
}