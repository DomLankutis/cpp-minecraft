#include "Mesh.hpp"

Mesh::Mesh(Vertex vertexInfo) {
    _indecieCount = vertexInfo.indices.size();

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    addVBO(3, vertexInfo.vertices);
    addVBO(3, vertexInfo.normals);
    addVBO(3, vertexInfo.colors);
    addVBO(2, vertexInfo.texCoords);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indecieCount * sizeof(unsigned int), vertexInfo.indices.data(), GL_STATIC_DRAW);
}

void Mesh::addVBO(int size, std::vector<GLfloat> data) {
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint)_vbos.size(), size, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(_vbos.size());
    _vbos.push_back(vbo);
}

Mesh::~Mesh() {
    if (_vao)
        glDeleteVertexArrays(1, &_vao);
    if (_ebo)
        glDeleteBuffers(1, &_ebo);
    for (auto &vbo : _vbos)
        glDeleteBuffers(1, &vbo);
}

void Mesh::draw(GLenum mode) {
    glBindVertexArray(_vao);
    glDrawElements(mode, _indecieCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
