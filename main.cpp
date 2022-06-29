//
// Created by karl on 6/28/22.
//

#include <iostream>
#include <vector>
#include <memory>

class objects;

class boringEngine {
private:
    std::vector<objects> objectList;

    void render(std::vector<objects> objectList) {

    }

    //TODO Change time type
    void update(std::vector<objects> objectList, double time) {

    }

//TODO Use proper time type
    void mainLoop(double deltaTime) {

        update(objectList, deltaTime);
        render(objectList);
    }

public:
    //TODO Create window, create context, etc.
    bool initEngine() {

        return true;
    }

    boringEngine() {
        initEngine();
        mainLoop(0);
    }

    ~boringEngine() {
        std::cout << "boring-engine destructor" << std::endl;
    }


};


int main() {
    std::unique_ptr<boringEngine> engine(new boringEngine());
    return 0;
}