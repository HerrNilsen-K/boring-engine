cmake_minimum_required(VERSION 3.5)
project(boring-engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GLEW REQUIRED)
link_libraries(${GLEW_LIBRARY})


add_executable(${PROJECT_NAME} src/main.cpp src/object.cpp src/object.hpp)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)