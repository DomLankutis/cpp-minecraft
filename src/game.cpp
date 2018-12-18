#include "game.hpp"

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

    _textureAtlas = Texture{"./Graphics/textures/textureAtlas.jpg"};

    _worldCamera = Camera{_window.getSize().x, _window.getSize().y};

    _lastMousePos = glm::vec2(_window.getSize().x / 2, _window.getSize().y / 2);

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

    std::vector<float> pos {
            -0.5, 0.5, 0.5,     // Front Top Left
            0.5,  0.5, 0.5,     // Front Top Right
            0.5, -0.5, 0.5,     // Front Bottom Right
            -0.5,-0.5, 0.5,     // Front Bottom Left

            -0.5, 0.5,-0.5,     // Back Top Left
            0.5,  0.5,-0.5,     // Back Top Right
            0.5, -0.5,-0.5,     // Back Bottom Right
            -0.5,-0.5,-0.5      // Back Bottom Left
    };

    float m = 0.25f;

    std::vector<float> textPos {
        0, 1,
        m, 1,
        m, 1 - m,
        0, 1 - m,
        0, 1,
        m, 1,
        m, 1 - m,
        0, 1 - m,
    };


    std::vector<unsigned int> posIndices = {
            0,3,2,  //Front
            2,1,0,

            1,5,6,	//Right
            6,2,1,

            5,4,7,	//Left
            7,6,5,

            4,7,3,	//Back
            3,0,4,

            4,5,1,	//Top
            1,0,4,

            3,2,6,	//Bottom
            6,7,3,
    };

    Mesh triangle {pos, textPos, posIndices};

    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(0, 0, -2));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0, 1, 1));

    while (_window.isOpen()) {

        sf::Event e{};
        while (_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                _window.close();
        }

        if (_window.hasFocus())
            updateMouse();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _worldCamera.update(getMouseOffset(), _dt.asSeconds());

        _textureAtlas.use();

        _shader.use();
        _shader.set("MVP", _worldCamera.getView() * model);

        triangle.draw(GL_TRIANGLES);
        _window.display();

        _dt = _deltaClock.restart();
    }
}