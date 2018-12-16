#ifndef CPP_MINECRAFT_GRAPHICSINFO_HPP
#define CPP_MINECRAFT_GRAPHICSINFO_HPP

class GraphicsInfo {
public:
    unsigned int VAO = 0;
    unsigned int indicesCount = 0;

    inline void reset() {
        VAO = 0;
        indicesCount = 0;
    }
};

#endif //CPP_MINECRAFT_GRAPHICSINFO_HPP
