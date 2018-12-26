#include "Block.hpp"

Block::Block() : _visable(true), _blockType(BlockType::Grass) {

}

const bool Block::isVisable() {
    return _visable;
}

void Block::setVisable(bool state) {
    _visable = state;
}

BlockType Block::getType() {
    return _blockType;
}

void Block::setType(BlockType type) {
    _blockType = type;
}

Vertex Block::buildFace(GLfloat v0[3], GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int width, int height, face side, glm::ivec3 chunkPos, unsigned int vertexCount, BlockType type) {

    glm::ivec3 offset {chunkPos * CHUNK_SIZE};

    std::vector<GLfloat> texPos {};

   if (side == face::LEFT || side == face::RIGHT)
       texPos = {
           0 , (GLfloat)height, (GLfloat)type,
           (GLfloat)width, (GLfloat)height, (GLfloat)type,
           (GLfloat)width, 0, (GLfloat)type,
           0, 0, (GLfloat)type,
       };

   if (side == face::FRONT || side == face::BACK)
       texPos = {
           (GLfloat)height, (GLfloat)height, (GLfloat)type,
           (GLfloat)height, 0, (GLfloat)type,
           0, 0, (GLfloat)type,
           0, (GLfloat)height, (GLfloat)type,
       };
   if (side == face::BOTTOM || side == face::TOP)
       texPos = {
           (GLfloat)height, 0, (GLfloat)type,
           (GLfloat)height, (GLfloat)height, (GLfloat)type,
           0, (GLfloat)height, (GLfloat)type,
           0, 0, (GLfloat)type,
       };

    return Vertex{
            {
                v0[0] + offset.x, v0[1] + offset.y, v0[2] + offset.z,
                v3[0] + offset.x, v3[1] + offset.y, v3[2] + offset.z,
                v2[0] + offset.x, v2[1] + offset.y, v2[2] + offset.z,
                v1[0] + offset.x, v1[1] + offset.y, v1[2] + offset.z,
            },

            {
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
            },

            {
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
            },

            texPos,

            {
                vertexCount + 0, vertexCount + 1,  vertexCount + 2,
                vertexCount + 2, vertexCount + 3,  vertexCount + 0,
            },
    };
}
