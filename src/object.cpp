//
// Created by karl on 6/30/22.
//

#include "object.hpp"

#include <iostream>
#include <string>

#include <GL/glew.h>

//Create debugCallback function
void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                   const void *userParam) {
    std::cout << "Debug message (" << source << "): " << message << std::endl;
}

sprite::sprite(std::vector<float>& vertices)
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
          rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
          scale(glm::vec3(1.0f, 1.0f, 1.0f)),
          model(glm::mat4(1.0f)),
          view(glm::mat4(1.0f)),
          projection(glm::mat4(1.0f)),
          MVP(glm::mat4(1.0f)) {
    //TODO Use proper debug callback
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, nullptr);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glBindVertexArray(0);

    //Create vertex shader and fragment shader
    std::string vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\n";

    std::string fragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n";


    //Create basic shader
    shader = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Compile vertex shader
    const char *vertexShaderSourcePtr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
    glCompileShader(vertexShader);
    //Check for errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        //TODO: Handle error
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Compile fragment shader
    const char *fragmentShaderSourcePtr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
    glCompileShader(fragmentShader);
    //Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Attach shaders to program
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);
    //Check for errors
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    glUseProgram(shader);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        //TODO: Handle error
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

sprite::~sprite() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);
}

object::object(std::vector<float> vertices)
        : m_sprite(vertices) {
}

void sprite::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}

void object::render() {
    m_sprite.render();

}

object::object(objectForm form)
        : m_sprite(form) {
}

sprite::sprite(objectForm form) {
    std::vector<float> vertices;
    switch (form) {
        case objectForm::RECTANGLE:
            //Assign values from -1 to 1  to form a rectangle
            vertices = {
                    -1.0f, -1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f
            };
            break;
    }

    sprite s(vertices);
    *this = std::move(s);
}


sprite &sprite::operator=(sprite &&other) noexcept {
    position = other.position;
    rotation = other.rotation;
    scale = other.scale;
    model = other.model;
    view = other.view;
    projection = other.projection;
    MVP = other.MVP;
    vao = other.vao;
    vbo = other.vbo;
    shader = other.shader;

    other.position = glm::vec3(0.0f, 0.0f, 0.0f);
    other.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    other.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    other.model = glm::mat4(1.0f);
    other.view = glm::mat4(1.0f);
    other.projection = glm::mat4(1.0f);
    other.MVP = glm::mat4(1.0f);
    other.vao = 0;
    other.vbo = 0;
    other.shader = 0;

    return *this;
}

sprite::sprite(sprite &&other) noexcept {
    position = other.position;
    rotation = other.rotation;
    scale = other.scale;
    model = other.model;
    view = other.view;
    projection = other.projection;
    MVP = other.MVP;
    vao = other.vao;
    vbo = other.vbo;
    shader = other.shader;

    //Set other to default state
    other.position = glm::vec3(0.0f, 0.0f, 0.0f);
    other.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    other.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    other.model = glm::mat4(1.0f);
    other.view = glm::mat4(1.0f);
    other.projection = glm::mat4(1.0f);
    other.MVP = glm::mat4(1.0f);
    other.vao = 0;
    other.vbo = 0;
    other.shader = 0;
}
