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
    Mesh(Vertex vertexInfo);
    ~Mesh();

public:
    void draw(GLenum);
};


#endif //CPP_MINECRAFT_MESH_H
