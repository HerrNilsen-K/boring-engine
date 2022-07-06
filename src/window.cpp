//
// Created by karl on 6/30/22.
//

#include "window.hpp"

#include <iostream>

window::window(int width, int height)
        : m_width(width), m_height(height) {
    glfwInit();

    m_window = glfwCreateWindow(width, height, "Boring Engine", NULL, NULL);
    glfwMakeContextCurrent(m_window);
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        //TODO Handle error
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(m_window, this);

}

bool window::isRunning() {
    return !glfwWindowShouldClose(m_window);
}

void window::poolEvents() {
    glfwPollEvents();
}

void window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

GLsizei window::getWidth() {
    GLsizei width;
    glfwGetWindowSize(m_window, &width, nullptr);
    return width;
}

GLsizei window::getHeight() {
    GLsizei height;
    glfwGetWindowSize(m_window, nullptr, &height);
    return height;
}

void window::onResizeInit(std::function<void(int, int)> callback) {
    m_onResize = callback;
    glfwSetFramebufferSizeCallback(m_window, onResize);
}

void window::onResize(GLFWwindow *window, int width, int height) {
    class window *w = reinterpret_cast<class window *>(glfwGetWindowUserPointer(window));
    w->m_onResize(width, height);
}
