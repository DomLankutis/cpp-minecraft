#include "Block.hpp"

Block::Block() : _active(true) {

}

bool Block::isActive() {
    return _active;
}

void Block::setActive(bool state) {
    _active = state;
}

Vertex Block::CreateCube(int x, int y, int z, unsigned int vertexCount) {
    float m = 0.25f;

    return Vertex {
            {
                    x + 1.0f, y + 0.0f, z + 0.0f,     // Front Top Left
                    x + 0.0f, y + 0.0f, z + 0.0f,     // Front Top Right
                    x + 0.0f, y + 1.0f, z + 0.0f,     // Front Bottom Right
                    x + 1.0f, y + 1.0f, z + 0.0f,     // Front Bottom Left
                    x + 1.0f, y + 0.0f, z + 1.0f,     // Back Top Left
                    x + 0.0f, y + 0.0f, z + 1.0f,     // Back Top Right
                    x + 0.0f, y + 1.0f, z + 1.0f,     // Back Bottom Right
                    x + 1.0f, y + 1.0f, z + 1.0f
            },

            {
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0,
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
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0,
            },

            {       0, 1,
                    m, 1,
                    m, 1 - m,
                    0, 1 - m,
                    0, 1,
                    m, 1,
                    m, 1 - m,
                    0, 1 - m,
            },

            {
                    vertexCount + 0, vertexCount + 3, vertexCount + 2,  //Front
                    vertexCount + 2, vertexCount + 1, vertexCount + 0,
                    vertexCount + 1, vertexCount + 5, vertexCount + 6,	//Right
                    vertexCount + 6, vertexCount + 2, vertexCount + 1,
                    vertexCount + 5, vertexCount + 4, vertexCount + 7,	//Left
                    vertexCount + 7, vertexCount + 6, vertexCount + 5,
                    vertexCount + 4, vertexCount + 7, vertexCount + 3,	//Back
                    vertexCount + 3, vertexCount + 0, vertexCount + 4,
                    vertexCount + 4, vertexCount + 5, vertexCount + 1,	//Top
                    vertexCount + 1, vertexCount + 0, vertexCount + 4,
                    vertexCount + 3, vertexCount + 2, vertexCount + 6,	//Bottom
                    vertexCount + 6, vertexCount + 7, vertexCount + 3
            },
    };
}