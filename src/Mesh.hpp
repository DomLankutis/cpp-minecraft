#ifndef CPP_MINECRAFT_MESH_H
#define CPP_MINECRAFT_MESH_H

#include "includes.hpp"

struct Vertex {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> lightVal;
    std::vector<GLuint> indices;

    Vertex& operator += (const Vertex& a) {
        this->vertices.insert(this->vertices.end(), a.vertices.begin(), a.vertices.end());
        this->texCoords.insert(this->texCoords.end(), a.texCoords.begin(), a.texCoords.end());
        this->lightVal.insert(this->lightVal.end(), a.lightVal.begin(), a.lightVal.end());
        this->indices.insert(this->indices.end(), a.indices.begin(), a.indices.end());
        return *this;
    }
};

class Mesh {
private:
    GLuint _vao;
    GLuint _ebo;
    std::vector<GLuint> _vbos;

    unsigned int _indecieCount;

private:
    void addVBO(int size, std::vector<GLfloat> data);

public:
    Mesh() = default;
    Mesh(Vertex vertexInfo);
    ~Mesh();

public:
    void draw(GLenum);
};

#endif //CPP_MINECRAFT_MESH_H
