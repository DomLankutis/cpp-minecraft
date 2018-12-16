#include "Mesh.hpp"

Mesh::Mesh(std::vector<float> vertex, std::vector<float>texture) {
    genVAO();

    _vertexPos = std::move(vertex);
    _texturePos = std::move(texture);

    addVBO(3, _vertexPos);
    addVBO(3, _texturePos);
}

void Mesh::addVBO(int size, std::vector<float> data) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)_vbos.size(), size, GL_FLOAT, GL_FALSE, size * sizeof(float),(void*)0);
    glEnableVertexAttribArray((GLuint)_vbos.size());
    _vbos.push_back(VBO);
}

void Mesh::genVAO() {
    if (_graphicsInfo.VAO != 0)
        _graphicsInfo.reset();

    glGenVertexArrays(1, &_graphicsInfo.VAO);
    glBindVertexArray(_graphicsInfo.VAO);
}

void Mesh::use() {
    glBindVertexArray(_graphicsInfo.VAO);
}

void Mesh::draw(GLenum mode, int start) {
    use();
    glDrawArrays(mode, 0, (GLsizei)_vertexPos.size());
}