//
// Created by karl on 6/28/22.
//

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

class objects {
};

using timeStamp = std::chrono::time_point<std::chrono::steady_clock>;

class boringEngine {
private:
    std::vector<objects> objectList;

    void render(std::vector<objects> objectList) {

    }

    void update(std::vector<objects> objectList, double time) {
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
            update(objectList, deltaTime);
            render(objectList);

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