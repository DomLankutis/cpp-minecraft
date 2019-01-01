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
    unsigned char _lightVal;
    BlockType _blockType;

public:
    Block();

public:
    const bool isVisable();
    void setVisable(bool state);
    BlockType getType();
    void setType(BlockType type);

    inline int getSunlight() { return (_lightVal >> 4) & 0xF; }
    inline void setSunlight(int val) {_lightVal = (_lightVal & 0xF) | (val << 4); }

    inline int getTorchLight() { return _lightVal & 0xF; }
    inline void setTorchLight(int val) {_lightVal = (_lightVal & 0xF0) | val; }

public:
    static Vertex buildFace(GLfloat v0[3], GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat width, GLfloat height,
            int lightVal, face side, glm::ivec3 chunkPos, unsigned int vertexCount, BlockType type);
};


#endif //CPP_MINECRAFT_BLOCK_H
