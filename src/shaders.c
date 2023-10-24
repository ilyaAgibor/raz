#include "shaders.h"

const char* read_file(const char* path){
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("shader %s not found\n", path);
        return NULL; 
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return NULL; 
    }

    size_t read_size = fread(content, 1, file_size, file);
    if (read_size == 0) {
        printf("cant read file\n");
        fclose(file);
        free(content);
        return NULL; 
    }
    content[read_size] = '\0';
    fclose(file);
    return content;
}

unsigned int create_shader(const char* vert, const char* frag){
    //reading shader files
    const char* vert_cont = read_file(vert);
    const char* frag_cont = read_file(frag);    

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    //compiling shaders
    glShaderSource(vertex_shader, 1, &vert_cont, NULL);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("faild compiling vertex shader %s with error:\n%s\n", vert, info_log);
    }

    glShaderSource(fragment_shader, 1, &frag_cont, NULL);
    glCompileShader(fragment_shader);
    memset(info_log, 0, 512);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("faild compiling fragment shader %s with error:\n%s\n", vert, info_log);
    }

    //linking shaders
    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    memset(info_log, 0, 512);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader, 512, NULL, info_log);
        printf("failed linking shaders:\n%s\n", info_log);
    }


    //deleting objects that are not needed anymorec
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(frag_cont);
    free(vert_cont);
    return shader;
}
