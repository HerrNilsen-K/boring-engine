//
// Created by karl on 6/30/22.
//

#ifndef BORING_ENGINE_WINDOW_HPP
#define BORING_ENGINE_WINDOW_HPP

#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window {
private:
    GLFWwindow *m_window;
    int m_width, m_height;
    std::function<void(int, int)> m_onResize;

    static void onResize(GLFWwindow *window, int width, int height);

public:
    void swapBuffers();

    void poolEvents();

    window(int width, int height);

    bool isRunning();

    void onResizeInit(std::function<void(int, int)> callback);

    GLsizei getWidth();

    GLsizei getHeight();

    //TODO add destructor
};


#endif //BORING_ENGINE_WINDOW_HPP
