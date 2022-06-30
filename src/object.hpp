//
// Created by karl on 6/30/22.
//

#ifndef BORING_ENGINE_OBJECT_HPP
#define BORING_ENGINE_OBJECT_HPP

#include <glm/glm.hpp>
#include <vector>

class object {
    /*PROPERTIES
     * vao,
     * vbo,
     * ebo (left out for now),
     * shader,
     * texture (left out for now)
     * position,
     * rotation,
     * scale,
     * */
protected:

    //Helper class for OpenGL
    class sprite {
    private:
        unsigned int vao, vbo;
        unsigned int shader;
        glm::vec3 position, rotation, scale;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 MVP;

    public:
        sprite(std::vector<float> vertices);

        ~sprite();

    };

    sprite m_sprite;

    object(std::vector<float> vertices);

};


#endif //BORING_ENGINE_OBJECT_HPP
