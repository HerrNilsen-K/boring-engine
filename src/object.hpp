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
    glm::vec3 translation, rotation, scale;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 MVP;

    unsigned int windowWidth, windowHeight;

public:
    explicit sprite(std::vector<float> &vertices, int windowWidth, int windowHeight);

    explicit sprite(objectForm form, int windowWidth, int windowHeight);

    sprite(sprite &&other) noexcept;

    sprite &operator=(sprite &&other) noexcept;

    void setTranslation(const glm::vec3 &translation);

    void setRotation(const glm::vec3 &rotation);

    void setScale(const glm::vec3 &scale);

    void setView(const glm::mat4 &view);

    void setProjection(const glm::mat4 &projection);

    void updateWindowSize(int width, int height);

    void render();

    void update(double delta);

    ~sprite();

};

class object {
    /*PROPERTIES
     * vao,
     * vbo,
     * ebo (left out for now),
     * shader,
     * texture (left out for now)
     * translation,
     * rotation,
     * scale,
     * */

protected:


    sprite m_sprite;

public:

    explicit object(std::vector<float> vertices, int windowWidth, int windowHeight);

    explicit object(objectForm form, int windowWidth, int windowHeight);

    void render();

    void update(double delta);

    void updateWindowSize(int width, int height);

};


#endif //BORING_ENGINE_OBJECT_HPP
