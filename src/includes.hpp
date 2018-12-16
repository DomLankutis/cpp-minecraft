#pragma once

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <SFML/Window.hpp>

#define Error(x) std::cout << "ERROR: " << x << std::endl
#define Log(x) std::cout << "LOG: " << x << std::endl