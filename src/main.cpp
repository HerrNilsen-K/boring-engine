//
// Created by karl on 6/28/22.
//

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

#include "object.hpp"


using timeStamp = std::chrono::time_point<std::chrono::steady_clock>;

class boringEngine {
private:
    std::vector<object> m_objectList;

    void render(std::vector<object> objectList) {

    }

    void update(std::vector<object> objectList, double time) {
    }

    [[noreturn]] void mainLoop() {
        //TODO change true to something like window.run() when window is implemented
        double deltaTime = 1;
        timeStamp previousTime = std::chrono::steady_clock::now();
        timeStamp currentTime = std::chrono::steady_clock::now();


        while (true) {
            previousTime = currentTime;
            currentTime = std::chrono::steady_clock::now();
            deltaTime = std::chrono::duration<double, std::milli>(currentTime - previousTime).count();
            update(m_objectList, deltaTime);
            render(m_objectList);

        }
    }

public:
    //TODO Create window, create context, etc.
    bool initEngine() {

        return true;
    }

    boringEngine() {
        initEngine();
        mainLoop();
    }

    ~boringEngine() {
        std::cout << "boring-engine destructor" << std::endl;
    }


};


int main() {
    std::unique_ptr<boringEngine> engine(new boringEngine());
    return 0;
}