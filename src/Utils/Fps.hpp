#ifndef CPP_MINECRAFT_FPS_HPP
#define CPP_MINECRAFT_FPS_HPP

#include "../includes.hpp"

class FPS {
private:
    unsigned int _frame;
    unsigned int _fps;
    sf::Clock _clock;

public:
    FPS() : _frame(0), _fps(0) {};

public:
    const unsigned int getFPS() const {return _fps;}

    void update() {
        if (_clock.getElapsedTime().asSeconds() >= 1.0f) {
            _fps = _frame;
            _frame = 0;
            _clock.restart();
        }
        ++_frame;
    }
};

#endif //CPP_MINECRAFT_FPS_HPP
