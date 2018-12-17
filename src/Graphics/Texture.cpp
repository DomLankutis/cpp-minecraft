#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

Texture::Texture(const char* path) {
    loadImage(path);
    genTexture();
    stbi_image_free(_imageData);
}

void Texture::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

void Texture::loadImage(const char* path) {
    stbi_set_flip_vertically_on_load(true);
    _imageData = stbi_load(path, &_width, &_height, &_nrChannels, 0);
    if (!_imageData)
        Error("Failed to load texture");
}

void Texture::genTexture() {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
}