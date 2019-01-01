#ifndef CPP_MINECRAFT_CHUNK_HPP
#define CPP_MINECRAFT_CHUNK_HPP

#include "Block.hpp"

class Chunk {
private:
    Block*** _blocks;
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
};

#endif //CPP_MINECRAFT_CHUNK_HPP
