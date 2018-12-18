#include "includes.hpp"

#include "./Graphics/shader.hpp"
#include "./Graphics/Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

class Game {
private:
    sf::Window _window;
    sf::Clock _deltaClock;
    sf::Time _dt;

    Texture _textureAtlas;
    Shader _shader;

    glm::vec2 _mousePos;
    glm::vec2 _lastMousePos;

    Camera _worldCamera;


private:
    void run();
    void updateMouse();
    glm::vec2 getMouseOffset();

public:
    Game();

public:
    void start();
};
