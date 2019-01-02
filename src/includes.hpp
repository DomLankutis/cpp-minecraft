#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <queue>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../lib/FastNoise/FastNoise.h"

#include <glad/glad.h>

#include <SFML/Window.hpp>


#define Error(x) std::cerr << "ERROR: " << x << std::endl
#define Log(x) std::cout << "LOG: " << x << std::endl

enum BlockType {
    Air = -1,
    Grass = 7,
    Dirt = 9,
};

constexpr int CHUNK_SIZE = 16;