#include "engine.h"


float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,   
         0.5f, -0.5f,  0.5f ,
         0.5f,  0.5f,  0.5f ,
        -0.5f,  0.5f,  0.5f ,
        -0.5f, -0.5f, -0.5f ,
         0.5f, -0.5f, -0.5f ,
         0.5f,  0.5f, -0.5f ,
        -0.5f,  0.5f, -0.5f     };

    // Define the indices for drawing the cube as triangles
unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        0, 4, 7,
        7, 3, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Top face
        3, 2, 6,
        6, 7, 3,

        // Bottom face
        0, 1, 5,
        5, 4, 0
    };

void run_engine(){
    clock_t t = clock();
    Window* window = create_window(1200, 800, "raz");
    Camera camera = {0};
    //setup opengl
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST); 

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
    mat4x4 prespective = prespective_matrix(800.0f/1200.0f, 90.0f, 1.0f, 15.0f);
    camera.position.y += 1.5f;
    mat4x4 view = look_at(camera.position, (vec3){0.0f,0.5f,1.0f}, (vec3){0.0f, 1.0f, 0.0f});
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("The main loop started after %f seconds\n", time_taken);
    float a = 0;
    while (!glfwWindowShouldClose(window->handle))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //
        glUseProgram(triangle_shader.id);
        trans = create_mat4x4(1.0f);
        trans = rotate_mat4x4(&trans, radians(a), (vec3){0.0f,1.0f,0.0f});
        trans = translate_mat4x4(&trans, (vec3){0.0,0.0f,5.0f});
        mat4x4 viewspace = multiply_mat4x4_mat4x4(&view, &trans);
        mat4x4 mvp = multiply_mat4x4_mat4x4( &prespective, &viewspace);
        set_uniform_mat4x4(&triangle_shader, "mvp", &mvp);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window->handle);
        glfwPollEvents();
        a += 1.0f;
    }
    delete_shader(&triangle_shader);
    close_window(window);
}