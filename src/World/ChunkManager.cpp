#include "ChunkManager.hpp"

ChunkManager::ChunkManager() {
    _fakeBlock.setType(BlockType::Air);
}

ChunkManager::~ChunkManager() {
    for (auto v : _worldMap) {
        delete(v.second);
    }
}

glm::ivec3 ChunkManager::worldPosToChunkPos(glm::vec3 pos) {
    pos /= CHUNK_SIZE;

    if (pos.x < 0)
        pos.x -= 1;
    if (pos.y < 0)
        pos.y -= 1;
    if (pos.z < 0)
        pos.z -= 1;

    return glm::ivec3{pos};
}

glm::ivec3 ChunkManager::worldPosToBlockPos(glm::vec3 pos) {
    return glm::ivec3{
        glm::floor(glm::mod(pos.x, (float)CHUNK_SIZE)),
        glm::floor(glm::mod(pos.y, (float)CHUNK_SIZE)),
        glm::floor(glm::mod(pos.z, (float)CHUNK_SIZE))
    };
}

Chunk& ChunkManager::getChunk(glm::vec3 pos) {
    glm::ivec3 chunkId = worldPosToChunkPos(pos);

    if (_worldMap.find(chunkId) == _worldMap.end()) {
#ifdef DEBUG
        Error("[ChunkManager] Chunk " << chunkId.x << " " << chunkId.y << " " << chunkId.z << " not found.");
#endif
        return _fakeChunk;
    } else {
        return *_worldMap[chunkId];
    }
}

Block& ChunkManager::getBlock(glm::vec3 pos) {
    glm::ivec3 blockPosition = worldPosToBlockPos(pos);
    return getChunk(pos).getBlock(blockPosition.x, blockPosition.y, blockPosition.z);
}

Block& ChunkManager::getBlock(glm::ivec3 id, glm::vec3 pos) {

    if (pos.x >= CHUNK_SIZE) {
        id.x++;
        pos.x = CHUNK_SIZE - pos.x;
    } else if (pos.x < 0) {
        id.x--;
        pos.x = CHUNK_SIZE + pos.x;
    }
    if (pos.y >= CHUNK_SIZE) {
        id.y++;
        pos.y = CHUNK_SIZE - pos.y;
    } else if (pos.y < 0) {
        id.y--;
        pos.y = CHUNK_SIZE + pos.y;
    }
    if (pos.z >= CHUNK_SIZE) {
        id.z++;
        pos.z = CHUNK_SIZE - pos.z;
    } else if (pos.z < 0) {
        id.z--;
        pos.z = CHUNK_SIZE + pos.z;
    }

    if (_worldMap.find(id) == _worldMap.end()) {
#ifdef DEBUG
        Error("[ChunkManager] Chunk is not loaded");
#endif
        return _fakeBlock;
    } else {
        return _worldMap[id]->getBlock(pos.x, pos.y, pos.z);
    }
}

bool ChunkManager::chunkHasData(glm::ivec3 id) {
    if (_worldMap.find(id) == _worldMap.end())
        return false;
    else if (_worldMap[id]->_isEmpty)
        return false;
    else
        return true;
}

bool ChunkManager::chunkSurrounded(glm::ivec3 id) {
    return (chunkHasData(id + glm::ivec3{1, 0, 0}) && chunkHasData(id + glm::ivec3{-1, 0, 0}) &&
            chunkHasData(id + glm::ivec3{0, 1, 0}) && chunkHasData(id + glm::ivec3{0, -1, 0}) &&
            chunkHasData(id + glm::ivec3{0, 0, 1}) && chunkHasData(id + glm::ivec3{0, 0, -1}) );
}

void ChunkManager::loadChunks() {
    while (!_toLoad.empty()) {
        if (_worldMap.find(_toLoad.front()) == _worldMap.end()) {
            _worldMap[_toLoad.front()] = new Chunk{_toLoad.front(), _toCreateSunLight};
            _toBuild.push(_toLoad.front());
        } else if (_worldMap[_toLoad.front()]->_isModified) {
            _toBuild.push(_toLoad.front());
        } else if (!chunkSurrounded(_toLoad.front())) {
            _toRender.push(_toLoad.front());
        }
        _toLoad.pop();
    }
}

Vertex ChunkManager::greedyMesh(glm::ivec3 chunkPos) {

    Vertex vertexInfo{};

    // Big thanks to roboleary for example of Greedy Mesh.

    int i = 0, j = 0, k = 0, l = 0, w = 0, h = 0, u = 0, v = 0, n = 0, side = 0;

    int x[3] = {0, 0, 0};
    int q[3] = {0, 0, 0};
    int du[3] = {0, 0, 0};
    int dv[3] = {0, 0, 0};

    Block mask[CHUNK_SIZE * CHUNK_SIZE]{};
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
                side = backface ? Face::RIGHT : Face::LEFT;
            else if (d == 1)
                side = backface ? Face::BOTTOM : Face::TOP;
            else if (d == 2)
                side = backface ? Face::FRONT : Face::BACK;

            for (x[d] = -1; x[d] < CHUNK_SIZE;) {

                n = 0;
                // v - Vertical
                // u - Horizotal
                for (x[v] = 0; x[v] < CHUNK_SIZE; ++x[v])
                    for (x[u] = 0; x[u] < CHUNK_SIZE; ++x[u]) {
                        b0 = (x[d] >= 0) ? getBlock(chunkPos, glm::vec3{x[0], x[1], x[2]}) : _fakeBlock;
                        b1 = (x[d] < CHUNK_SIZE - 1) ? getBlock(chunkPos,
                                                                glm::vec3{x[0] + q[0], x[1] + q[1], x[2] + q[2]})
                                                     : _fakeBlock;

                        if (side == RIGHT) {
                            b1.setTorchLight(getBlock(chunkPos, glm::vec3{x[0] + q[0] - 1, x[1] + q[1],
                                                                          x[2] + q[2]}).getTorchLight());
                            b1.setSunlight(getBlock(chunkPos, glm::vec3{x[0] + q[0] - 1, x[1] + q[1],
                                                                        x[2] + q[2]}).getSunlight());
                        } else if (side == LEFT) {
                            b0.setTorchLight(getBlock(chunkPos, glm::vec3{x[0] + 1, x[1], x[2]}).getTorchLight());
                            b0.setSunlight(getBlock(chunkPos, glm::vec3{x[0] + 1, x[1], x[2]}).getSunlight());
                        }
                        if (side == BOTTOM) {
                            b1.setTorchLight(getBlock(chunkPos, glm::vec3{x[0] + q[0], x[1] + q[1] - 1,
                                                                          x[2] + q[2]}).getTorchLight());
                            b1.setSunlight(getBlock(chunkPos, glm::vec3{x[0] + q[0], x[1] + q[1] - 1,
                                                                        x[2] + q[2]}).getSunlight());
                        } else if (side == TOP) {
                            b0.setTorchLight(getBlock(chunkPos, glm::vec3{x[0], x[1] + 1, x[2]}).getTorchLight());
                            b0.setSunlight(getBlock(chunkPos, glm::vec3{x[0], x[1] + 1, x[2]}).getSunlight());
                        }
                        if (side == FRONT) {
                            b1.setTorchLight(getBlock(chunkPos, glm::vec3{x[0] + q[0], x[1] + q[1],
                                                                          x[2] + q[2] - 1}).getTorchLight());
                            b1.setSunlight(getBlock(chunkPos, glm::vec3{x[0] + q[0], x[1] + q[1],
                                                                        x[2] + q[2] - 1}).getSunlight());
                        } else if (side == BACK) {
                            b0.setTorchLight(getBlock(chunkPos, glm::vec3{x[0], x[1], x[2] + 1}).getTorchLight());
                            b0.setSunlight(getBlock(chunkPos, glm::vec3{x[0], x[1], x[2] + 1}).getSunlight());
                        }

                        mask[n++] = (b0.getType() == b1.getType())
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
                                        mask[n + w].getTorchLight() == mask[n].getTorchLight() &&
                                        mask[n + w].getSunlight() == mask[n].getSunlight(); w++) {}

                            bool done = false;

                            for (h = 1; j + h < CHUNK_SIZE; h++) {
                                for (k = 0; k < w; k++) {
                                    if (mask[n + k + h * CHUNK_SIZE].getType() == BlockType::Air ||
                                        mask[n + k + h * CHUNK_SIZE].getType() != mask[n].getType() ||
                                        mask[n + k + h * CHUNK_SIZE].getTorchLight() != mask[n].getTorchLight() ||
                                        mask[n + k + h * CHUNK_SIZE].getSunlight() != mask[n].getSunlight()) {
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

                                vertexInfo += Block::buildFace(v0, v1, v2, v3, w, h,
                                                               mask[n].getTorchLight() + mask[n].getSunlight(),
                                                               Face(side), chunkPos, vertexInfo.vertices.size() / 3,
                                                               mask[n].getType());
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
    return vertexInfo;
}

void ChunkManager::buildChunks() {
    std::vector<std::pair<std::future<Vertex>, glm::ivec3>> vertexInfo;
    bool firstRun = true;
    while (!_toBuild.empty()) {
        if (firstRun) {
            calculateSunLight();
            calculateTorchLight();
            firstRun = false;
        }
        glm::ivec3 chunkPos = _toBuild.front();
        vertexInfo.emplace_back(std::pair<std::future<Vertex>, glm::ivec3>{std::async(&ChunkManager::greedyMesh,
                this, chunkPos), chunkPos});
        _toBuild.pop();
    }

    for (auto it = vertexInfo.begin(); it != vertexInfo.end(); it++) {
        Vertex vertexInf = it->first.get();
        if (vertexInf.vertices.size() == 0)
            _worldMap[it->second]->_isEmpty = true;
        _worldMap[it->second]->createMesh(vertexInf);
    }
}

void ChunkManager::addTorchLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    if (getBlock(sourceWorldPos).getTorchLight() + 2 <= lightLevel) {
        if (getBlock(sourceWorldPos).getType() == BlockType::Air) {
            _toCreateTorchLight.push(sourceWorldPos);
            getBlock(sourceWorldPos).setTorchLight(lightLevel - 1);
        }
        getChunk(sourceWorldPos)._isModified = true;
    }
}

void ChunkManager::addSunLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    if (getBlock(sourceWorldPos).getSunlight() + 2 <= lightLevel) {
        if (getBlock(sourceWorldPos).getType() == BlockType::Air) {
            _toCreateSunLight.push(sourceWorldPos);
            getBlock(sourceWorldPos).setSunlight(lightLevel - 1);
        }
        getChunk(sourceWorldPos)._isModified = true;
    }
}

void ChunkManager::removeSunLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    int neighbourLevel = getBlock(sourceWorldPos).getSunlight();
    if (neighbourLevel != 0 && neighbourLevel < lightLevel) {
        getBlock(sourceWorldPos).setSunlight(0);
        _toRemoveSunLight.push(lightRemoveNode{sourceWorldPos, neighbourLevel});
        getChunk(sourceWorldPos)._isModified = true;
    } else if (neighbourLevel >= lightLevel) {
        _toCreateSunLight.push(sourceWorldPos);
        getChunk(sourceWorldPos)._isModified = true;
    }
}

void ChunkManager::removeTorchLight(glm::ivec3 sourceWorldPos, int lightLevel) {
    int neighbourLevel = getBlock(sourceWorldPos).getTorchLight();
    if (neighbourLevel != 0 && neighbourLevel < lightLevel) {
        getBlock(sourceWorldPos).setTorchLight(0);
        _toRemoveTorchLight.push(lightRemoveNode{sourceWorldPos, neighbourLevel});
        getChunk(sourceWorldPos)._isModified = true;
    } else if (neighbourLevel >= lightLevel) {
        _toCreateTorchLight.push(sourceWorldPos);
        getChunk(sourceWorldPos)._isModified = true;
    }
}

void ChunkManager::calculateSunLight() {
    while (!_toRemoveSunLight.empty()) {
        glm::ivec3 blockWorldPos = _toRemoveSunLight.front().worldPosIndex;
        int lightLevel = getBlock(blockWorldPos).getSunlight();

        if (lightLevel == 15) {
            getBlock(blockWorldPos).setSunlight(0);
            _toRemoveSunLight.push(lightRemoveNode{blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel});
        }

        removeSunLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        removeSunLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        removeSunLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        removeSunLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        removeSunLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toRemoveSunLight.pop();
    }
    while (!_toCreateSunLight.empty()) {
        glm::ivec3 blockWorldPos = _toCreateSunLight.front();
        int lightLevel = getBlock(blockWorldPos).getSunlight();

        if (lightLevel == 15)
            addSunLight(blockWorldPos + glm::ivec3{0, -1, 0}, 16);
        else
            addSunLight(blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel);

        addSunLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        addSunLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        addSunLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        addSunLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        addSunLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toCreateSunLight.pop();
    }
}

void ChunkManager::calculateTorchLight() {
    while (!_toRemoveTorchLight.empty()) {
        glm::ivec3 blockWorldPos = _toRemoveTorchLight.front().worldPosIndex;
        int lightLevel = getBlock(blockWorldPos).getTorchLight();

        removeTorchLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        removeTorchLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toRemoveTorchLight.pop();
    }

    while (!_toCreateTorchLight.empty()) {
        glm::ivec3 blockWorldPos = _toCreateTorchLight.front();
        int lightLevel = getBlock(blockWorldPos).getTorchLight();

        addTorchLight(blockWorldPos + glm::ivec3{1, 0, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{-1, 0, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 1, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, -1, 0}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 0, 1}, lightLevel);
        addTorchLight(blockWorldPos + glm::ivec3{0, 0, -1}, lightLevel);

        _toCreateTorchLight.pop();
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

float intbound(float s, float ds) {
    if (ds < 0) {
        return intbound(-s, -ds);
    } else {
        s = glm::mod(s, 1.0f);
        return (1-s)/ds;
    }
}

void ChunkManager::castRay(Camera &camera) {

    int range = 3;

    glm::vec3 camFront = camera.getFront();
    glm::ivec3 pos {glm::floor(camera.getPosition())};

    glm::ivec3 step {
        (camFront.x > 0) ? 1 : (camFront.x < 0) ? -1 : 0,
        (camFront.y > 0) ? 1 : (camFront.y < 0) ? -1 : 0,
        (camFront.z > 0) ? 1 : (camFront.z < 0) ? -1 : 0
    };

    if (step.x != 0 && step.y != 0 && step.z != 0) {
        glm::vec3 tMax{
                intbound(camera.getPosition().x, camFront.x),
                intbound(camera.getPosition().y, camFront.y),
                intbound(camera.getPosition().z, camFront.z),
        };

        glm::vec3 tDelta{
                (float)step.x / camFront.x,
                (float)step.y / camFront.y,
                (float)step.z / camFront.z,
        };

        glm::vec3 face{};

        for (;;) {
            if (getBlock(pos).getType() != BlockType::Air) {
                _selectedPos = pos;
                _selectedFace = face;
                break;
            }
            if (tMax.x < tMax.y) {
                if (tMax.x < tMax.z) {
                    if (tMax.x > range) break;
                    pos.x += step.x;
                    tMax.x += tDelta.x;
                    face.x = -step.x;
                    face.y = 0;
                    face.z = 0;
                } else {
                    if (tMax.z > range) break;
                    pos.z += step.z;
                    tMax.z += tDelta.z;
                    face.x = 0;
                    face.y = 0;
                    face.z = -step.z;
                }
            } else if (tMax.y < tMax.z) {
                    if (tMax.y > range) break;
                    pos.y += step.y;
                    tMax.y += tDelta.y;
                    face.x = 0;
                    face.y = -step.y;
                    face.z = 0;
                } else {
                    if (tMax.z > range) break;
                    pos.z += step.z;
                    tMax.z += tDelta.z;
                    face.x = 0;
                    face.y = 0;
                    face.z = -step.z;
                }
            }
        }
    }

void ChunkManager::createBlock(BlockType blockType) {
    if (_selectedPos != glm::vec3{}) {
        getBlock(_selectedPos + _selectedFace).setType(blockType);
        _toRemoveSunLight.push(lightRemoveNode{_selectedPos + _selectedFace,
                                               getBlock(_selectedPos + _selectedFace).getSunlight()});
        getChunk(_selectedPos + _selectedFace)._isModified = true;
    }
}

void ChunkManager::destroyBlock() {
    if (_selectedPos != glm::vec3{}) {
        getBlock(_selectedPos).setType(BlockType::Air);
        _toCreateTorchLight.push(_selectedPos + _selectedFace);
        _toCreateSunLight.push(_selectedPos + _selectedFace);
        if (_selectedFace != glm::vec3{0, 1, 0}) {
            _toCreateTorchLight.push(_selectedPos + glm::vec3{0, 1, 0});
            _toCreateSunLight.push(_selectedPos + glm::vec3{0, 1, 0});
        }
        _toRemoveTorchLight.push(lightRemoveNode{_selectedPos,
                                               getBlock(_selectedPos).getTorchLight()});
        getChunk(_selectedPos)._isModified = true;
    }
}

void ChunkManager::update(float dt, Camera &camera) {
    for (int y = -1; y < 1; y++)
    for (int z = 0; z < 4; z++)
    for (int x = 0; x < 4; x++) {
        _toLoad.push(glm::ivec3{x, y, z});
    }

    castRay(camera);

    loadChunks();
    getBlock(glm::ivec3{5, 5, 5}).setTorchLight(15);
    _toCreateTorchLight.push(glm::ivec3{5, 5, 5});
    buildChunks();
    renderChunks();
}