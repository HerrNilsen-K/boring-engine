//
// Created by karl on 6/30/22.
//

#ifndef BORING_ENGINE_WINDOW_HPP
#define BORING_ENGINE_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window {
private:
    GLFWwindow *m_window;
    int m_width, m_height;

public:
    void swapBuffers();

    void poolEvents();

    window(int width, int height);

    bool isRunning();
};


#endif //BORING_ENGINE_WINDOW_HPP
