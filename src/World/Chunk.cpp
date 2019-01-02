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

Chunk::Chunk(glm::ivec3 pos) {
    _blocks = new Block** [CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        _blocks[i] = new Block* [CHUNK_SIZE];
        for (int j = 0; j < 16; j++) {
            _blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }

    for (int z = 0; z < CHUNK_SIZE; z++)
    for (int x = 0; x < CHUNK_SIZE; x++) {
        int y = (int)(WORLD_NOISE.GetNoise(x + (pos.x * CHUNK_SIZE), z + (pos.z * CHUNK_SIZE)) * NOISE_MULTIPLIER) + - (pos.y * CHUNK_SIZE);
        if (y >= 0 && y <= CHUNK_SIZE - 1)
            _blocks[y][z][x].setType(BlockType::Grass);
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

Block& Chunk::getBlock(int x, int y, int z) {
    return _blocks[y][z][x];
}

void Chunk::createMesh(Vertex& vertexInfo) {
    _chunkMesh = new Mesh{vertexInfo};
}

void Chunk::render(GLenum) {
    _chunkMesh->draw(GL_TRIANGLES);
}
