#ifndef CPP_MINECRAFT_CHUNKMANAGER_HPP
#define CPP_MINECRAFT_CHUNKMANAGER_HPP

#include "../includes.hpp"
#include "Chunk.hpp"

struct lightRemoveNode {
    int worldPosIndex;
    int val;
};

class ChunkManager {
private:
    std::unordered_map<int, Chunk*> _worldMap;
    std::queue<int> _toLoad;
    std::queue<int> _toBuild;
    std::queue<int> _toRender;
    std::queue<int> _toCreateLight;
    std::queue<lightRemoveNode> _toRemoveLight;


    Block _fakeBlock {};
    Chunk _fakeChunk {};

private:
    inline int posToIndex(glm::ivec3 pos);
    inline int posToIndex(int x, int y, int z);
    inline glm::ivec3 indexToPos(int index);

    glm::ivec3 worldPosToChunkPos(glm::ivec3 pos);
    glm::ivec3 chunkPosToWorldPos(int index, glm::ivec3);

    Chunk& getChunk(glm::ivec3 pos);
    Block& getBlock(glm::ivec3 pos);
    Block& getBlock(int id, glm::vec3 pos);
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
