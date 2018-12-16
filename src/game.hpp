#include "includes.hpp"

#include "./Graphics/shader.hpp"
#include "Mesh.hpp"

class Game {
private:
    static sf::Window _window;
    static sf::Event _event;

    static Shader _shader;

    bool _running;

private:
    void Run();

public:
    Game();
    ~Game() = default;

    void Start();
};
