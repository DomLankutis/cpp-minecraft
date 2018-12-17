#ifndef CPP_MINECRAFT_TEXTURE_H
#define CPP_MINECRAFT_TEXTURE_H

#include "../includes.hpp"

class Texture {
private:
    int _width, _height, _nrChannels;
    unsigned int _texture;
    unsigned char* _imageData;

private:
    void loadImage(const char*);
    void genTexture();

public:
    Texture() = default;
    Texture(const char* path);

public:
    void use();
};


#endif //CPP_MINECRAFT_TEXTURE_H
