#include "game.hpp"

FastNoise WORLD_NOISE;

Game::Game() {
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.majorVersion = 4;
    contextSettings.minorVersion = 3;
    contextSettings.attributeFlags = sf::ContextSettings::Core;

    _window.create(sf::VideoMode{WIDTH, HEIGHT}, "Minecraft", sf::Style::Titlebar, contextSettings);
    _window.setMouseCursorVisible(false);
    _window.setMouseCursorGrabbed(true);

    if (!gladLoadGL()) {
        Error("failed to load opengl extensions");
        return;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, _window.getSize().x, _window.getSize().y);

    _shader = Shader{"./Graphics/shaders/vShader.glsl", "./Graphics/shaders/fShader.glsl"};

    _textureAtlas = Texture{"./Graphics/textures/textureAtlas.png", 4};

    _playerCamera = Camera{_window.getSize().x, _window.getSize().y};

    _mouse = Mouse{_window};

    std::srand((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    WORLD_NOISE.SetSeed(std::rand());
    WORLD_NOISE.SetNoiseType(FastNoise::Simplex);
}

void Game::start() {
    run();
}

void Game::run() {

    while (_window.isOpen()) {

        sf::Event e{};
        while (_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                _window.close();
                exit(0);
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::I)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                if (e.key.code == sf::Keyboard::K)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        if (_window.hasFocus())
            _mouse.update(_window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _playerCamera.update(_mouse.getOffset(), _dt);

        _textureAtlas.use();

        _shader.use();
        _shader.set("MVP", _playerCamera.getView());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _chunkManager.destroyBlock();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            _chunkManager.createBlock(BlockType::Dirt);
        }

        _chunkManager.update(_dt, _playerCamera);
        _window.display();

        _fps.update();
        _window.setTitle(std::to_string(_fps.getFPS()) + " " + std::to_string(_playerCamera.getPosition().x) + " " + std::to_string( _playerCamera.getPosition().y) + " " + std::to_string( _playerCamera.getPosition().z ));
        _dt = _deltaClock.restart().asSeconds();
    }
}