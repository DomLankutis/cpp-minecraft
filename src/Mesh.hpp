#ifndef CPP_MINECRAFT_MESH_H
#define CPP_MINECRAFT_MESH_H

#include "includes.hpp"
#include "./Graphics/GraphicsInfo.hpp"

class Mesh {
private:
    std::vector<float> _vertexPos;
    std::vector<unsigned int> _indices;
    std::vector<float> _texturePos;
    GraphicsInfo _graphicsInfo;

    std::vector<unsigned int> _vbos;

private:
    void use();

public:
    Mesh() = default;
    Mesh(std::vector<float>,std::vector<float>, std::vector<unsigned int>);
    ~Mesh() = default;

public:
    void genVAO();
    void genEBO(std::vector<unsigned int>);
    void addVBO(int, std::vector<float>);
    void draw(GLenum);

};


#endif //CPP_MINECRAFT_MESH_H
