//
// Created by dom on 16/12/18.
//

#ifndef CPP_MINECRAFT_MESH_H
#define CPP_MINECRAFT_MESH_H

#include "includes.hpp"
#include "./Graphics/GraphicsInfo.hpp"

class Mesh {
private:
    std::vector<float> _vertexPos;
    std::vector<float> _texturePos;
    GraphicsInfo _graphicsInfo;

    std::vector<unsigned int> _vbos;

private:
    void use();

public:
    Mesh() = default;
    Mesh(std::vector<float>, std::vector<float>);
    ~Mesh() = default;

public:
    void addVBO(int, std::vector<float>);
    void genVAO();
    void draw(GLenum, int = 0);

};


#endif //CPP_MINECRAFT_MESH_H
