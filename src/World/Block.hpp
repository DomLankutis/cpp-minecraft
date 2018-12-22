#ifndef CPP_MINECRAFT_BLOCK_H
#define CPP_MINECRAFT_BLOCK_H

#include "../includes.hpp"
#include "../Mesh.hpp"

class Block {
private:
    bool _active;
    BlockType blockType;

public:
    Block();

public:
    bool isActive();
    void setActive(bool state);

    static Vertex CreateCube(int x, int y, int z, unsigned int vertexCount);
};


#endif //CPP_MINECRAFT_BLOCK_H
