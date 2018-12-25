#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

Texture::Texture(const char* path, int texInRow) {
    loadImage(path);
    genTexture(texInRow);
    stbi_image_free(_imageData);
}

void Texture::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
}

void Texture::loadImage(const char* path) {
    _imageData = stbi_load(path, &_width, &_height, &_nrChannels, 0);
    if (!_imageData)
        Error("Failed to load texture");
}

void Texture::genTexture(int texInRow) {
    GLsizei size = _width / texInRow;
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, size, size, texInRow * texInRow, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, _width);
    int layer = 0;
    for (int col = 0; col < texInRow; ++col)
    for (int row = 0; row < texInRow; ++row) {
        int xoff = row % texInRow * size;
        int yoff = col % texInRow * size;
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, xoff);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, yoff);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer++, size, size, 1, GL_RGBA, GL_UNSIGNED_BYTE, _imageData);
    }
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}
