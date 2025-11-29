//
// Created by htlix on 2025/10/29.
//

#include "core//Texture2D.h"
#include "core/Utils.h"

Texture2D::Texture2D(const std::string &fileName) {
    textureID = Utils::loadTexture(fileName.c_str());
}

void Texture2D::bind(GLuint texture) {
    glActiveTexture(GL_TEXTURE0 + texture);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
