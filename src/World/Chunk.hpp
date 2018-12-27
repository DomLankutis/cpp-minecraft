#ifndef CPP_MINECRAFT_CHUNK_HPP
#define CPP_MINECRAFT_CHUNK_HPP

#include "Block.hpp"

class Chunk {
private:
    Block*** _blocks;
    unsigned char _lightMap[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh* _chunkMesh;

public:
    bool _isModified;

public:
    Chunk();
    ~Chunk();

public:
    void createMesh(Vertex& vertexInfo);
    void render(GLenum);
    Block& getBlock(int x, int y, int z);
    inline int getSunlight(int x, int y, int z) { return (_lightMap[y][z][x] >> 4) & 0xF; }
    inline void setSunlight(int x, int y, int z, int val) { _lightMap[y][z][x] = (_lightMap[x][y][z] & 0xF) | (val << 4); }
    inline int getTorchLight(int x, int y, int z) { return _lightMap[y][z][x] & 0xF; }
    inline void setTorchLight(int x, int y, int z, int val) { _lightMap[y][z][x] = (_lightMap[x][y][z] & 0xF0) | val; }
};

#endif //CPP_MINECRAFT_CHUNK_HPP
