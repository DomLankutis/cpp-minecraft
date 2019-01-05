#include "includes.hpp"

#include "./Utils/Fps.hpp"
#include "./Graphics/shader.hpp"
#include "./Graphics/Texture.hpp"
#include "./World/Block.hpp"
#include "./World/Chunk.hpp"
#include "./World/ChunkManager.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

class Game {
private:
    sf::Window _window;
    sf::Clock _deltaClock;
    sf::Time _dt;

    FPS _fps;

    Texture _textureAtlas;
    Shader _shader;

    glm::vec2 _mousePos;
    glm::vec2 _lastMousePos;

    Camera _playerCamera;

    ChunkManager _chunkManager;

private:
    void run();
    void updateMouse();
    glm::vec2 getMouseOffset();

public:
    Game();

public:
    void start();
};
