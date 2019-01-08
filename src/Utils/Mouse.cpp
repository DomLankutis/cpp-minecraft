#include "Mouse.hpp"

Mouse::Mouse(sf::Window &window) {
    _lastMousePos = glm::vec2(window.getSize().x / 2, window.getSize().y / 2);
    _limiterMax = 0.2;
}

glm::vec2 Mouse::getOffset() {
    return _mousePos - _lastMousePos;
}

void Mouse::update(float &dt, sf::Window &window) {
    if ((_limiterTime += dt) >= _limiterMax) {
        _limiterTime = 0;
        _canClick = true;
    }

    sf::Vector2i sm = sf::Mouse::getPosition(window);
    _mousePos = glm::vec2(sm.x, sm.y);
    sf::Mouse::setPosition(sf::Vector2i((int)window.getSize().x / 2, (int)window.getSize().y / 2), window);
}

const bool Mouse::isButtonPressed(sf::Mouse::Button button) {
    bool eval = (sf::Mouse::isButtonPressed(button) && _canClick);
    _canClick = eval ? false : _canClick;
    return eval;
}
