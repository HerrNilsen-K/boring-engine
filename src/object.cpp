//
// Created by karl on 6/30/22.
//

#include "object.hpp"

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Create debugCallback function
void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                   const void *userParam) {
    std::cout << "Debug message (" << source << "): " << message << std::endl;
}

sprite::sprite(std::vector<float> &vertices, int windowWidth, int windowHeight)
        :
        translation(glm::vec3(0.0f, 0.0f, 0.0f)),
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
            "uniform mat4 MVP;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * MVP;\n"
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
        //TODO: Handle error
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

object::object(std::vector<float> vertices, int windowWidth, int windowHeight)
        : m_sprite(vertices, windowWidth, windowHeight) {
}

void sprite::render() {
    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}

void object::render() {
    m_sprite.render();

}

object::object(objectForm form, int windowWidth, int windowHeight)
        : m_sprite(form, windowWidth, windowHeight) {
    switch (form) {
        case objectForm::RECTANGLE:
            m_sprite.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            m_sprite.setTranslation(glm::vec3(00.f, 0.0f, 0.0f));
            m_sprite.setScale(glm::vec3(1.0f, 1.0f, 1.0f));

            //The setProjection function is identical to the commented one, but it is uses screen coordinates
            // m_sprite.setProjection(glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f));
            m_sprite.setProjection(glm::ortho(-static_cast<float>(windowWidth) / 2.0f,
                                              static_cast<float>(windowWidth) / 2.0f,
                                              -static_cast<float>(windowHeight) / 2.0f,
                                              static_cast<float>(windowHeight) / 2.0f,
                                              -1.0f, 1.0f));
            m_sprite.setView(glm::mat4(1.0f));
            break;
    }
}

sprite::sprite(objectForm form, int windowWidth, int windowHeight) {
    std::vector<float> vertices;
    switch (form) {
        case objectForm::RECTANGLE:
            /* NDC
            vertices = {
                    -1.0f, -1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f
            };*/
            //The values are identical to the NDCs above, but they are in screen coordinates
            vertices = {
                    -static_cast<float>(windowWidth) / 2.0f, -static_cast<float>(windowHeight) / 2.0f, 0.0f,
                    static_cast<float>(windowWidth) / 2.0f, -static_cast<float>(windowHeight) / 2.0f, 0.0f,
                    -static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f, 0.0f,
                    static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f, 0.0f,
                    static_cast<float>(windowWidth) / 2.0f, -static_cast<float>(windowHeight) / 2.0f, 0.0f,
                    -static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f, 0.0f
            };
            break;
    }

    sprite s(vertices, windowWidth, windowHeight);
    *this = std::move(s);
}


sprite &sprite::operator=(sprite &&other) noexcept {
    translation = other.translation;
    rotation = other.rotation;
    scale = other.scale;
    model = other.model;
    view = other.view;
    projection = other.projection;
    MVP = other.MVP;
    vao = other.vao;
    vbo = other.vbo;
    shader = other.shader;

    other.translation = glm::vec3(0.0f, 0.0f, 0.0f);
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
    translation = other.translation;
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
    other.translation = glm::vec3(0.0f, 0.0f, 0.0f);
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


void sprite::setRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
}

void sprite::setScale(const glm::vec3 &scale) {
    this->scale = scale;
}

void sprite::setView(const glm::mat4 &view) {
    this->view = view;
}

void sprite::setProjection(const glm::mat4 &projection) {
    this->projection = projection;
}

void sprite::update(double delta) {
    model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, translation);
    view = glm::mat4(1.0f);
    MVP = projection * view * model;

    glUseProgram(shader);
    glUniformMatrix4fv(
            glGetUniformLocation(shader, "MVP"),
            1, GL_TRUE, glm::value_ptr(MVP));
}

void object::update(double delta) {
    m_sprite.update(delta);
}

void sprite::setTranslation(const glm::vec3 &translation) {
    this->translation = translation;
}

void sprite::updateWindowSize(int width, int height) {
    windowHeight = height;
    windowWidth = width;
}

void object::updateWindowSize(int width, int height) {
    m_sprite.updateWindowSize(width, height);
}
