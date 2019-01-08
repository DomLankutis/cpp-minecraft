#ifndef CPP_VOXEL_ENGINE_MOUSE_HPP
#define CPP_VOXEL_ENGINE_MOUSE_HPP

#include "../includes.hpp"


class Mouse {
public:
    Mouse() = default;
    explicit Mouse(sf::Window &window);

public:
    glm::vec2 _mousePos;
    glm::vec2 _lastMousePos;

public:
    void update(sf::Window &window);
    glm::vec2 getOffset();
};


#endif //CPP_VOXEL_ENGINE_MOUSE_HPP
