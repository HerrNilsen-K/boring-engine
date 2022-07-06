//
// Created by karl on 6/28/22.
//

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

#include "object.hpp"
#include "window.hpp"

using timeStamp = std::chrono::time_point<std::chrono::steady_clock>;

class boringEngine {
private:
    window m_window;

    double deltaTime = 1;

    //List of objects in a scene
    std::vector<object> m_objectList;

    void render(std::vector<object> &objectList) {

        for (auto &object : objectList) {
            object.render();
        }

        m_window.swapBuffers();
    }

    void update(std::vector<object> &objectList, double time) {
        for (auto &object : objectList) {
            object.update(time);
        }
    }

    void mainLoop() {
        timeStamp previousTime = std::chrono::steady_clock::now();
        timeStamp currentTime = std::chrono::steady_clock::now();

        m_objectList.emplace_back(objectForm::RECTANGLE, m_window.getWidth(), m_window.getHeight());

        while (m_window.isRunning()) {
            previousTime = currentTime;
            currentTime = std::chrono::steady_clock::now();
            deltaTime = std::chrono::duration<double, std::milli>(currentTime - previousTime).count();

            m_window.poolEvents();
            update(m_objectList, deltaTime);
            render(m_objectList);

        }
    }

public:
    //TODO Create window, create context, etc.
    [[maybe_unused]]bool initEngine() {

        return true;
    }

    boringEngine()
            : m_window(800, 600) {
        initEngine();

        m_window.onResizeInit([&](int width, int height) {
            std::cout << "Resized to " << width << "x" << height << std::endl;
            for(auto &object : m_objectList) {
                object.updateWindowSize(width, height);
            }
            glViewport(0, 0, m_window.getWidth(), m_window.getHeight());
            update(m_objectList, deltaTime);
            render(m_objectList);
        });
    }

    void start() {
        mainLoop();
    }

    ~boringEngine() {
        std::cout << "boring-engine destructor" << std::endl;
    }


};


int main() {
    std::unique_ptr<boringEngine> engine(new boringEngine());
    engine->start();
    return 0;
}