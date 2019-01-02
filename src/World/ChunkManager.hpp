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
    std::queue<glm::ivec3> _toCreateTorchLight;
    std::queue<glm::ivec3> _toCreateSunLight;
    std::queue<lightRemoveNode> _toRemoveTorchLight;


    Block _fakeBlock {};
    Chunk _fakeChunk {};

private:
    glm::ivec3 worldPosToChunkPos(glm::vec3 pos);
    glm::ivec3 worldPosToBlockPos(glm::vec3 pos);
    Chunk& getChunk(glm::ivec3 pos);
    Block& getBlock(glm::ivec3 pos);
    Block& getBlock(glm::ivec3 id, glm::vec3 pos);
    bool chunkHasData(glm::ivec3 id);
    bool chunkSurrounded(glm::ivec3 id);

    void addTorchLight(glm::ivec3 sourceWorldPos, int lightLevel);
    void addSunLight(glm::ivec3 sourceWorldPos, int lightLevel);
    void removeTorchLight(glm::ivec3 sourceWorldPos, int lightLevel);
    void removeSunLight(glm::ivec3 sourceWorldPos, int lightLevel);

    void loadChunks();
    void buildChunks();
    void calculateSunLight();
    void calculateTorchLight();
    void renderChunks();

public:
    ChunkManager();
    ~ChunkManager();

public:
    void update(float dt, glm::vec3 cameraPosition);

};


#endif //CPP_MINECRAFT_CHUNKMANAGER_HPP
