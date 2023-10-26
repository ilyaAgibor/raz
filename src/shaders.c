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

Shader create_shader(const char* vert, const char* frag){
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
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    memset(info_log, 0, 512);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("failed linking shaders:\n%s\n", info_log);
    }


    //deleting objects that are not needed anymorec
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(frag_cont);
    free(vert_cont);
    Shader shader = {0};
    shader.id = shader_program;
    return shader;
}

int get_uniform(Shader* shader, const char* name){
    UniformNote* tmp = shader->head;
    UniformNote* slave = shader->head;
    while(tmp){
        if(!strcmp(tmp->cach->name, name) ){
            return tmp->cach->id;
        }
        tmp = tmp->next;
    }
    int res = glGetUniformLocation(shader->id, name);
    if(res < 0){
        printf("coudn't find uniform with name %s\n", name);
    }
    else{
        shader->head = malloc(sizeof(UniformNote));
        shader->head->cach = malloc(sizeof(UniformCach));
        shader->head->next = slave;
        strcpy(shader->head->cach->name, name);
        shader->head->cach->id = res;
    }
    return res;
}

void delete_shader(Shader* shader){
    UniformNote* tmp = shader->head;
    while(tmp){
        UniformNote* slave = tmp;
        tmp = tmp->next;
        free(slave->cach);
        free(slave);
    }
}

void set_uniform_bool(Shader* shader, const char* name, bool value){
    glUniform1i(get_uniform(shader, name), (int)value);
}
void set_uniform_int(Shader* shader, const char* name, int value){
    glUniform1i(get_uniform(shader, name), (int)value);
}
void set_uniform_float(Shader* shader, const char* name, float value){
    glUniform1f(get_uniform(shader, name), value);
}
void set_uniform_vec2(Shader* shader, const char* name, float x, float y){
    glUniform2f(get_uniform(shader, name), x, y);
}
void set_uniform_vec3(Shader* shader, const char* name, float x, float y, float z){
    glUniform3f(get_uniform(shader, name), x, y, z);
}
void set_uniform_vec4(Shader* shader, const char* name, float x, float y, float z, float w){
    glUniform4f(get_uniform(shader, name), x, y, z, w);
}

void set_uniform_mat4x4(Shader* shader, const char* name, mat4x4* matrix){
    glUniformMatrix4fv(get_uniform(shader, name), 1, GL_FALSE, matrix->data);
}