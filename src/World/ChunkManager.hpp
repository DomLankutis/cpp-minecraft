#ifndef CPP_MINECRAFT_CHUNKMANAGER_HPP
#define CPP_MINECRAFT_CHUNKMANAGER_HPP

#include "../includes.hpp"
#include "Chunk.hpp"

struct lightRemoveNode {
    glm::ivec3 worldPosIndex;
    int val;
};

class ChunkManager {
private:
    std::unordered_map<glm::ivec3, Chunk*> _worldMap;
    std::queue<glm::ivec3> _toLoad;
    std::queue<glm::ivec3> _toBuild;
    std::queue<glm::ivec3> _toRender;
    std::queue<glm::ivec3> _toCreateLight;
    std::queue<lightRemoveNode> _toRemoveLight;


    Block _fakeBlock {};
    Chunk _fakeChunk {};

private:
    glm::ivec3 worldPosToChunkPos(glm::ivec3 pos);
    glm::ivec3 chunkPosToWorldPos(glm::ivec3 id, glm::ivec3 pos);

    Chunk& getChunk(glm::ivec3 pos);
    Block& getBlock(glm::ivec3 pos);
    Block& getBlock(glm::ivec3 id, glm::vec3 pos);
    bool chunkSurrounded(glm::ivec3 id);

    void addTorchLight(glm::ivec3 sourceWorldPos, int lightLevel);
    void removeTorchLight(glm::ivec3 sourceWorldPos, int lightLevel);

    void loadChunks();
    void buildChunks();
    void calculateTorchLight();
    void renderChunks();

public:
    ChunkManager();
    ~ChunkManager();

public:
    void update(float dt, glm::vec3 cameraPosition);

};


#endif //CPP_MINECRAFT_CHUNKMANAGER_HPP
