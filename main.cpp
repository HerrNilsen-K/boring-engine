//
// Created by karl on 6/28/22.
//

#include <iostream>

class boringEngine {
public:
    boringEngine() {
        std::cout << "boring-engine constructor" << std::endl;
    }
    ~boringEngine() {
        std::cout << "boring-engine destructor" << std::endl;
    }

};


int main() {

    return EXIT_SUCCESS;
}