//
// Created by htlix on 2025/10/29.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <string>

class Texture2D {
public:
    Texture2D() {}
    Texture2D(const std::string &fileName);

    void bind(GLuint texture = 0);

private:
    GLuint textureID;
};

#endif // TEXTURE_H