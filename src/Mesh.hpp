#ifndef CPP_MINECRAFT_MESH_H
#define CPP_MINECRAFT_MESH_H

#include "includes.hpp"

struct Vertex {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint> indices;

    Vertex& operator += (const Vertex& a) {
            this->vertices.insert(this->vertices.end(), a.vertices.begin(), a.vertices.end());
            this->normals.insert(this->normals.end(), a.normals.begin(), a.normals.end());
            this->colors.insert(this->colors.end(), a.colors.begin(), a.colors.end());
            this->texCoords.insert(this->texCoords.end(), a.texCoords.begin(), a.texCoords.end());
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
