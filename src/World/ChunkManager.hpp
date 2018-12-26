#ifndef CPP_MINECRAFT_CHUNKMANAGER_HPP
#define CPP_MINECRAFT_CHUNKMANAGER_HPP

#include "../includes.hpp"
#include "Chunk.hpp"

class ChunkManager {
private:
    std::unordered_map<glm::ivec3, Chunk*> _worldMap;
    std::queue<glm::ivec3> _toLoad;
    std::queue<glm::ivec3> _toBuild;
    std::queue<glm::ivec3> _toRender;

    Block _fakeBlock {};

private:
    Block& getBlock(glm::vec3 pos);
    Block& getBlock(glm::ivec3 id, glm::vec3 pos);
    bool chunkSurrounded(glm::ivec3 id);
    void loadChunks();
    void buildChunks();
    void renderChunks();

public:
    ChunkManager();
    ~ChunkManager();

public:
    void update(float dt, glm::vec3 cameraPosition);

};


#endif //CPP_MINECRAFT_CHUNKMANAGER_HPP
