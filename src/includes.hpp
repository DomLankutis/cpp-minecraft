#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <SFML/Window.hpp>

#define Error(x) std::cout << "ERROR: " << x << std::endl
#define Log(x) std::cout << "LOG: " << x << std::endl