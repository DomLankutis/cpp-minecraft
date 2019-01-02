#include "game.hpp"

FastNoise WORLD_NOISE;

Game::Game() {
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.majorVersion = 4;
    contextSettings.minorVersion = 3;
    contextSettings.attributeFlags = sf::ContextSettings::Core;

    _window.create(sf::VideoMode{1920, 1080}, "Minecraft", sf::Style::Titlebar, contextSettings);
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

    _worldCamera = Camera{_window.getSize().x, _window.getSize().y};

    _lastMousePos = glm::vec2(_window.getSize().x / 2, _window.getSize().y / 2);

    std::srand((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    WORLD_NOISE.SetSeed(std::rand());
    WORLD_NOISE.SetNoiseType(FastNoise::Simplex);
}

void Game::start() {
    run();
}

void Game::updateMouse() {
    sf::Vector2i sm = sf::Mouse::getPosition(_window);
    _mousePos = glm::vec2(sm.x, sm.y);
    sf::Mouse::setPosition(sf::Vector2i((int)_window.getSize().x / 2, (int)_window.getSize().y / 2), _window);
}

glm::vec2 Game::getMouseOffset() {
    return _mousePos - _lastMousePos;
}

void Game::run() {

    while (_window.isOpen()) {

        sf::Event e{};
        while (_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                _window.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::I)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                if (e.key.code == sf::Keyboard::K)
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        if (_window.hasFocus())
            updateMouse();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _worldCamera.update(getMouseOffset(), _dt.asSeconds());

        _textureAtlas.use();

        _shader.use();
        _shader.set("MVP", _worldCamera.getView());

        _chunkManager.update(_dt.asSeconds(), _worldCamera.getPosition());

        _window.display();

        _fps.update();
        _window.setTitle(std::to_string(_fps.getFPS()));
        _dt = _deltaClock.restart();
    }
}