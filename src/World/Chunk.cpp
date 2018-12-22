#include "Chunk.hpp"

Chunk::Chunk() {
    _blocks = new Block** [CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        _blocks[i] = new Block* [CHUNK_SIZE];
        for (int j = 0; j < 16; j++) {
            _blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk() {
    for(int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            delete [] _blocks[i][j];
        }
        delete [] _blocks[i];
    }
    delete [] _blocks;
    delete _chunkMesh;
}

void Chunk::createMesh() {
    Vertex finalMeshInfo {};
    for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
    for (int z = 0; z < CHUNK_SIZE; z++) {

        if (!_blocks[x][y][z].isActive())
            continue;

        Vertex cubeInfo = Block::CreateCube(x, y, z, finalMeshInfo.vertices.size() / 3);
        finalMeshInfo += cubeInfo;

    }}}
    _chunkMesh = new Mesh{finalMeshInfo};
}

void Chunk::render(GLenum) {
    _chunkMesh->draw(GL_TRIANGLES);
}