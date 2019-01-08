#include "includes.hpp"

#include "./Utils/Fps.hpp"
#include "./Utils/Mouse.hpp"
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
    float _dt;

    FPS _fps;
    Mouse _mouse;

    Texture _textureAtlas;
    Shader _shader;

    Camera _playerCamera;

    ChunkManager _chunkManager;

private:
    void run();

public:
    Game();

public:
    void start();
};
