#include "Camera.hpp"

Camera::Camera(unsigned int windowWidth, unsigned int windowHeight) :
    _front(glm::vec3(0.0f, 0.0f, -1.0f)),
    _pos(glm::vec3(0.0f, 0.0f, 0.0f)),
    _lastX(windowWidth / 2), _lastY(windowHeight / 2)
{
    _projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
}

void Camera::updateView() {
    _view = _projection * glm::lookAt(
            _pos,
            _pos + _front,
            glm::vec3(0, 1.0f, 0)
    );
}

void Camera::handleKeyboard(float dt) {
    float CAMERA_SPEED = movementSpeed * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(CAMERA_SPEED * _front);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(-CAMERA_SPEED * _front);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(-glm::normalize(glm::cross(_front, glm::vec3(0, 1, 0))) * CAMERA_SPEED);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(glm::normalize(glm::cross(_front, glm::vec3(0, 1, 0))) * CAMERA_SPEED);
}

void Camera::handleMouse(glm::vec2 m, float dt) {

    _yaw = glm::mod(_yaw + (m.x * mouseSensitivity), 360.0f);
    _pitch += -m.y * mouseSensitivity;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    _front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
    _front.y = sin(glm::radians(_pitch));
    _front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
    _front = glm::normalize(_front);
}

void Camera::update(glm::vec2 mPos, float dt) {
    handleMouse(mPos, dt);
    handleKeyboard(dt);
    updateView();
}
