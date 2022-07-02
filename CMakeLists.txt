cmake_minimum_required(VERSION 3.5)
project(boring-engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
link_libraries(${GLEW_LIBRARY})
link_libraries(${GLFW3_LIBRARY})


add_executable(${PROJECT_NAME} src/main.cpp src/object.cpp src/object.hpp src/window.cpp src/window.hpp)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
