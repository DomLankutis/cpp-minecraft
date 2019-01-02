#include "ChunkManager.hpp"

ChunkManager::ChunkManager() {
    _fakeBlock.setType(BlockType::Air);
}

ChunkManager::~ChunkManager() {
    for (auto v : _worldMap) {
        delete(v.second);
    }
}

glm::ivec3 ChunkManager::worldPosToChunkPos(glm::ivec3 pos) {
    pos /= CHUNK_SIZE;
    return glm::ivec3{pos};
}

glm::ivec3 ChunkManager::chunkPosToWorldPos(glm::ivec3 index, glm::ivec3 pos) {
    return pos * index;
}

glm::ivec3 worldPosToBlockPos(glm::vec3 pos) {
    return glm::ivec3{
        glm::floor(glm::mod(pos.x, (float)CHUNK_SIZE)),
        glm::floor(glm::mod(pos.y, (float)CHUNK_SIZE)),
        glm::floor(glm::mod(pos.z, (float)CHUNK_SIZE))
    };
}

Chunk& ChunkManager::getChunk(glm::ivec3 pos) {
    glm::ivec3 chunkId = worldPosToChunkPos(pos);

    if (_worldMap.find(chunkId) == _worldMap.end()) {
        Error("[ChunkManager] Chunk " << chunkId.x << " " << chunkId.y << " " << chunkId.z << " not found.");
        return _fakeChunk;
    } else {
        return *_worldMap[chunkId];
    }
}

Block& ChunkManager::getBlock(glm::ivec3 pos) {
    glm::ivec3 blockPosition = worldPosToBlockPos(pos);
    return getChunk(pos).getBlock(blockPosition.x, blockPosition.y, blockPosition.z);
}

Block& ChunkManager::getBlock(glm::ivec3 id, glm::vec3 pos) {
    if (_worldMap.find(id) == _worldMap.end()) {
        Error("[ChunkManager] Chunk is not loaded");
        return _fakeBlock;
    } else {
        if ( (pos.x >= 0 && CHUNK_SIZE > pos.x) && (pos.y >= 0 && CHUNK_SIZE > pos.y) && (pos.z >= 0 && CHUNK_SIZE > pos.z) )
            return _worldMap[id]->getBlock(pos.x, pos.y, pos.z);
        else
            return _fakeBlock;
    }
}

bool ChunkManager::chunkSurrounded(glm::ivec3 id) {
    return ((_worldMap.find(id + glm::ivec3{1, 0, 0}) != _worldMap.end())  &&
            (_worldMap.find(id + glm::ivec3{-1, 0, 0}) != _worldMap.end()) &&
            (_worldMap.find(id + glm::ivec3{0, 1, 0})!= _worldMap.end())  &&
            (_worldMap.find(id + glm::ivec3{0, -1, 0}) != _worldMap.end()) &&
            (_worldMap.find(id + glm::ivec3{0, 0, 1})!= _worldMap.end())   &&
            (_worldMap.find(id + glm::ivec3{0, 0, -1}) != _worldMap.end())
            );
}

void ChunkManager::loadChunks() {
    while (!_toLoad.empty()) {
        if (_worldMap.find(_toLoad.front()) == _worldMap.end()) {
            _worldMap[_toLoad.front()] = new Chunk{_toLoad.front()};
            _toBuild.push(_toLoad.front());
        } else if (!chunkSurrounded(_toLoad.front())){
            _toRender.push(_toLoad.front());
        }
        _toLoad.pop();
    }
}

void ChunkManager::buildChunks() {
    calculateTorchLight();
    while (!_toBuild.empty()) {
        Vertex vertexInfo {};

        // Big thanks to roboleary for example of Greedy Mesh.

        int i = 0, j = 0, k = 0, l = 0, w = 0, h = 0, u = 0, v = 0, n = 0, side = 0;

        int x[3] = {0, 0, 0};
        int q[3] = {0, 0, 0};
        int du[3] = {0, 0, 0};
        int dv[3] = {0, 0, 0};

        Block mask[CHUNK_SIZE * CHUNK_SIZE] {};
        Block b0, b1;

        for (bool backface = true, b = false; b != backface; backface = backface && b, b = !b) {
            for (int d = 0; d < 3; d++) {

                u = (d + 1) % 3;
                v = (d + 2) % 3;

                x[0] = 0;
                x[1] = 0;
                x[2] = 0;
                q[0] = 0;
                q[1] = 0;
                q[2] = 0;
                q[d] = 1;

                if (d == 0)
                    side = backface ? face::RIGHT : face::LEFT;
                else if (d == 1)
                    side = backface ? face::BOTTOM : face::TOP;
                else if (d == 2)
                    side = backface ? face::FRONT : face::BACK;

                for (x[d] = -1; x[d] < CHUNK_SIZE;) {

                    n = 0;
                    // v - Vertical
                    // u - Horizotal
                    for (x[v] = 0; x[v] < CHUNK_SIZE; ++x[v])
                        for (x[u] = 0; x[u] < CHUNK_SIZE; ++x[u]) {
                            b0 = (x[d] >= 0) ? getBlock(_toBuild.front(), glm::vec3{x[0], x[1], x[2]}) : this->_fakeBlock;
                            b1 = (x[d] < CHUNK_SIZE - 1) ? getBlock(_toBuild.front(), glm::vec3{x[0] + q[0], x[1] + q[1], x[2] + q[2]}) : this->_fakeBlock;

                            mask[n++] = (b0.getType() == b1.getType() && b0.getTorchLight() == b1.getTorchLight())
                                        ? this->_fakeBlock
                                        : backface ? b1 : b0;
                        }

                    x[d]++;
                    n = 0;

                    for (j = 0; j < CHUNK_SIZE; j++)
                        for (i = 0; i < CHUNK_SIZE;) {
                            if (mask[n].getType() != BlockType::Air) {
                                for (w = 1; i + w < CHUNK_SIZE && mask[n + w].getType() != BlockType::Air &&
                                            mask[n + w].getType() == mask[n].getType() &&
                                            mask[n + w].getTorchLight() == mask[n].getTorchLight(); w++) {}

                                bool done = false;

                                for (h = 1; j + h < CHUNK_SIZE; h++) {
                                    for (k = 0; k < w; k++) {
                                        if (mask[n + k + h * CHUNK_SIZE].getType() == BlockType::Air ||
                                            mask[n + k + h * CHUNK_SIZE].getType() != mask[n].getType() ||
                                                mask[n + k + h * CHUNK_SIZE].getTorchLight() != mask[n].getTorchLight()) {
                                            done = true;
                                            break;
                                        }
                                    }
                                    if (done)
                                        break;
                                }

                                if (mask[n].getType() != BlockType::Air) {
                                    x[u] = i;
                                    x[v] = j;

                                    du[0] = 0;
                                    du[1] = 0;
                                    du[2] = 0;
                                    du[u] = w;

                                    dv[0] = 0;
                                    dv[1] = 0;
                                    dv[2] = 0;
                                    dv[v] = h;

                                    GLfloat v0[3] = {(GLfloat) (x[0]), (GLfloat) (x[1]), (GLfloat) (x[2])};

                                    GLfloat v1[3] = {(GLfloat) (x[0] + du[0]), (GLfloat) (x[1] + du[1]),
                                                     (GLfloat) (x[2] + du[2])};

                                    GLfloat v2[3] = {(GLfloat) (x[0] + du[0] + dv[0]), (GLfloat) (x[1] + du[1] + dv[1]),
                                                     (GLfloat) (x[2] + du[2] + dv[2])};

                                    GLfloat v3[3] = {(GLfloat) (x[0] + dv[0]), (GLfloat) (x[1] + dv[1]),
                                                     (GLfloat) (x[2] + dv[2])};

                                    vertexInfo += Block::buildFace(v0, v1, v2, v3, w, h, mask[n].getTorchLight(),
                                            face(side), _toBuild.front(), vertexInfo.vertices.size() / 3, mask[n].getType());
                                }

                                for (l = 0; l < h; ++l) {
                                    for (k = 0; k < w; ++k) {
                                        mask[n + k + l * CHUNK_SIZE] = this->_fakeBlock;
                                    }
                                }

                                i += w;
                                n += w;
                            } else {
                                i++;
                                n++;
                            }
                        }
                }
            }
        }
        _worldMap[_toBuild.front()]->createMesh(vertexInfo);
        _toBuild.pop();
    }
}

void ChunkManager::addTorchLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    if (getBlock(sourceWorldPos).getTorchLight() + 2 <= lightLevel) {
        if (getBlock(sourceWorldPos).getType() == BlockType::Air)
            _toCreateLight.push(sourceWorldPos);
        getBlock(sourceWorldPos).setTorchLight(lightLevel - 1);
    }
}

void ChunkManager::removeTorchLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    int neighbourLevel = getBlock(sourceWorldPos).getTorchLight();
    if (neighbourLevel != 0 && neighbourLevel < lightLevel) {
        getBlock(sourceWorldPos).getTorchLight();
        _toRemoveLight.push(lightRemoveNode{sourceWorldPos, neighbourLevel});
    } else if (neighbourLevel >= lightLevel) {
        _toCreateLight.push(sourceWorldPos);
    }
}

void ChunkManager::calculateTorchLight() {
    while (!_toRemoveLight.empty()) {
        glm::ivec3 blockWorldPos = _toRemoveLight.front().worldPosIndex;
        int lightLevel = getBlock(blockWorldPos).getTorchLight();

        removeTorchLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toRemoveLight.pop();
    }

    while (!_toCreateLight.empty()) {
        glm::ivec3 blockWorldPos = _toCreateLight.front();
        int lightLevel = getBlock(blockWorldPos).getTorchLight();

        addTorchLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toCreateLight.pop();
    }
}

void ChunkManager::renderChunks() {
    while (!_toRender.empty()) {
        if (_worldMap.find(_toRender.front()) == _worldMap.end()) {
            Error("RENDER - Chunk not loaded");
        } else {
            _worldMap[_toRender.front()]->render(GL_TRIANGLES);
        }
        _toRender.pop();
    }
}

bool first = true;

void ChunkManager::update(float dt, glm::vec3 cameraPosition) {
    for (int y = -1; y < 2; y++)
    for (int z = 0; z < 4; z++)
    for (int x = 0; x < 4; x++) {
        _toLoad.push(glm::ivec3{x, y, z});
    }
    loadChunks();
    buildChunks();
    renderChunks();
}