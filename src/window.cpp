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
