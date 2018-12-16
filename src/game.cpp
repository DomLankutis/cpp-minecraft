#include "game.hpp"

sf::Window Game::_window;
sf::Event Game::_event;

Shader Game::_shader;


Game::Game() {
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.majorVersion = 4;
    contextSettings.minorVersion = 3;
    contextSettings.attributeFlags = sf::ContextSettings::Core;
    _window.create(sf::VideoMode{1920, 1080}, "Minecraft", sf::Style::Titlebar, contextSettings);
    _window.setVerticalSyncEnabled(true);
    if (!gladLoadGL()) {
        Error("failed to load opengl extensions");
        return;
    }
    glViewport(0, 0, _window.getSize().x, _window.getSize().y);

    _shader = Shader{"./Graphics/shaders/vShader.glsl", "./Graphics/shaders/fShader.glsl"};

    _running = true;
}

void Game::Start() {
    Run();
}

void Game::Run() {

    std::vector<float> pos {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
    };

    std::vector<float> col {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };

    Mesh triangle {pos, col};

    while (_running) {

        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                _running = false;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _shader.use();
        triangle.draw(GL_TRIANGLES);

        _window.display();
    }
}