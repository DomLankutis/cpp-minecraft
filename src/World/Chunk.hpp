#ifndef CPP_MINECRAFT_CHUNK_HPP
#define CPP_MINECRAFT_CHUNK_HPP

#include "Block.hpp"

class Chunk {
private:
    Block*** _blocks;
    Mesh* _chunkMesh;

public:
    Chunk();
    ~Chunk();

public:
    void createMesh();
    void update(float dt);
    void render(GLenum);

};

#endif //CPP_MINECRAFT_CHUNK_HPP
