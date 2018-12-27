#ifndef CPP_MINECRAFT_CAMERA_H
#define CPP_MINECRAFT_CAMERA_H

#include "includes.hpp"

class Camera {
private:
    glm::vec3 _pos;
    glm::vec3 _front;

    glm::mat4 _view;
    glm::mat4 _projection;

    float _lastX;
    float _lastY;

    float _yaw = 0;
    float _pitch = 0;

    bool _fistMouse = true;

private:
    void handleKeyboard(float);
    void handleMouse(glm::vec2, float);
    void updateView();

public:
    Camera() = default;
    Camera(unsigned int, unsigned int);


    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1;

public:
    template <typename T>
    void move(T value) {_pos += value;}
    void update(glm::vec2, float);
    const glm::mat4 getView() { return _view;}
    const glm::vec3 getPosition() { return _pos; }
};


#endif //CPP_MINECRAFT_CAMERA_H
