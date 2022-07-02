//
// Created by karl on 6/30/22.
//

#ifndef BORING_ENGINE_OBJECT_HPP
#define BORING_ENGINE_OBJECT_HPP

#include <glm/glm.hpp>
#include <vector>
#include <map>

enum class objectForm {
    RECTANGLE
};


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
    explicit sprite(std::vector<float> &
    vertices);

    explicit sprite(objectForm form);

    sprite(sprite &&other) noexcept;

    sprite &operator=(sprite &&other) noexcept;

    void render();

    ~sprite();

};

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


    sprite m_sprite;

public:

    explicit object(std::vector<float>
                    vertices);

    explicit object(objectForm
                    form);

    void render();


};


#endif //BORING_ENGINE_OBJECT_HPP
