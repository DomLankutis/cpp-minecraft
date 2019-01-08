#ifndef CPP_VOXEL_ENGINE_MOUSE_HPP
#define CPP_VOXEL_ENGINE_MOUSE_HPP

#include "../includes.hpp"


class Mouse {
private:
    float _limiterMax;
    float _limiterTime;
    bool _canClick;

public:
    Mouse() = default;
    explicit Mouse(sf::Window &window);

public:
    glm::vec2 _mousePos;
    glm::vec2 _lastMousePos;

public:
    void update(float &dt, sf::Window &window);
    glm::vec2 getOffset();
    const bool isButtonPressed(sf::Mouse::Button button);
};


#endif //CPP_VOXEL_ENGINE_MOUSE_HPP
