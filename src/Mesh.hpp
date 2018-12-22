#ifndef CPP_MINECRAFT_MESH_H
#define CPP_MINECRAFT_MESH_H

#include "includes.hpp"
#include "./Graphics/GraphicsInfo.hpp"

struct Vertex {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint> indices;

    Vertex& operator += (const Vertex& a) {
            this->vertices.insert(this->vertices.end(), std::make_move_iterator(a.vertices.begin()), std::make_move_iterator(a.vertices.end()));
            this->normals.insert(this->normals.end(), std::make_move_iterator(a.normals.begin()), std::make_move_iterator(a.normals.end()));
            this->colors.insert(this->colors.end(), std::make_move_iterator(a.colors.begin()), std::make_move_iterator(a.colors.end()));
            this->texCoords.insert(this->texCoords.end(), std::make_move_iterator(a.texCoords.begin()), std::make_move_iterator(a.texCoords.end()));
            this->indices.insert(this->indices.end(), std::make_move_iterator(a.indices.begin()), std::make_move_iterator(a.indices.end()));

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
