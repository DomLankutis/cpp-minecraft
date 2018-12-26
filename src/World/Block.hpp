#ifndef CPP_MINECRAFT_BLOCK_H
#define CPP_MINECRAFT_BLOCK_H

#include "../includes.hpp"
#include "../Mesh.hpp"

enum face {
    FRONT,
    BACK,
    RIGHT,
    LEFT,
    TOP,
    BOTTOM,
};

class Block {
private:
    bool _visable;
    BlockType _blockType;

public:
    Block();

public:
    const bool isVisable();
    void setVisable(bool state);
    BlockType getType();
    void setType(BlockType type);

public:
    static Vertex buildFace(GLfloat v0[3], GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat width, GLfloat height,
            face side, glm::ivec3 chunkPos, unsigned int vertexCount, BlockType type);
};


#endif //CPP_MINECRAFT_BLOCK_H
