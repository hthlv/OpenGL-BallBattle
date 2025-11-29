//
// Created by htlix on 2025/10/23.
//

#include "core/Utils.h"

#include <fstream>
#include <iostream>

#include "SOIL2/SOIL2.h"

using std::cout;
using std::endl;

string Utils::readShaderSource(const char *filePath) {
    string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        std::cout << "File is not exist: " << filePath << std::endl;
        return "";
    }
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

void Utils::printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = new char[len];
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log: " << log << endl;
        delete[] log;
    }
}

void Utils::printProgramLog(GLuint program) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = new char[len];
        glGetProgramInfoLog(program, len, &chWrittn, log);
        cout << "Program Info Log: " << log << endl;
        delete[] log;
    }
}

GLuint Utils::createShader(const char *shaderFilePath, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    string shaderSource = Utils::readShaderSource(shaderFilePath);
    const char *shaderStr = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderStr, NULL);
    glCompileShader(shader);
    checkOpenGLError();
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != 1) {
        cout << "Shader compilation failed, the file is: " << shaderFilePath
             << endl;
        printShaderLog(shader);
    }
    return shader;
}

bool Utils::checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

GLuint Utils::createShaderProgram(const char *vsFilePath,
                                  const char *fsFilePath) {
    GLint linked;

    GLuint vShader = createShader(vsFilePath, GL_VERTEX_SHADER);
    GLuint fShader = createShader(fsFilePath, GL_FRAGMENT_SHADER);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "Program linking failed!" << endl;
        printProgramLog(vfProgram);
        glDeleteProgram(vfProgram);
        vfProgram = 0;
    }
    // // 检查活动的uniform数量
    // GLint numUniforms = 0;
    // glGetProgramiv(vfProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
    // cout << "Active uniforms in program " << vfProgram << ": " << numUniforms
    // << endl;
    //
    // // 列出所有uniform
    // for (GLint i = 0; i < numUniforms; ++i) {
    //     char uniformName[256];
    //     GLsizei length;
    //     GLint size;
    //     GLenum type;
    //     glGetActiveUniform(vfProgram, i, sizeof(uniformName), &length, &size,
    //     &type, uniformName); cout << "  Uniform " << i << ": " << uniformName
    //     << " (type: " << type << ")" << endl;
    // }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return vfProgram;
}

GLuint Utils::createShaderProgram(const char *vp, const char *gp,
                                  const char *fp) {
    GLint linked;

    GLuint vShader = createShader(vp, GL_VERTEX_SHADER);
    GLuint gShader = createShader(gp, GL_GEOMETRY_SHADER);
    GLuint fShader = createShader(fp, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, gShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    checkOpenGLError();
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "Program linking failed!" << endl;
        printProgramLog(program);
        glDeleteProgram(program);
        program = 0;
    }
    glDeleteShader(vShader);
    glDeleteShader(gShader);
    glDeleteShader(fShader);
    return program;
}

GLuint Utils::createShaderProgram(const char *vp, const char *tCS,
                                  const char *tES, const char *fp) {
    GLint linked;

    GLuint vShader = createShader(vp, GL_VERTEX_SHADER);
    GLuint tcShader = createShader(tCS, GL_TESS_CONTROL_SHADER);
    GLuint tesShader = createShader(tES, GL_TESS_EVALUATION_SHADER);
    GLuint fShader = createShader(fp, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, tcShader);
    glAttachShader(program, tesShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    checkOpenGLError();
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "Program linking failed!" << endl;
        printProgramLog(program);
        glDeleteProgram(program);
        program = 0;
    }
    glDeleteShader(vShader);
    glDeleteShader(tcShader);
    glDeleteShader(tesShader);
    glDeleteShader(fShader);
    return program;
}

GLuint Utils::createShaderProgram(const char *vp, const char *tCS,
                                  const char *tES, const char *gp,
                                  const char *fp) {
    GLint linked;

    GLuint vShader = createShader(vp, GL_VERTEX_SHADER);
    GLuint tcShader = createShader(tCS, GL_TESS_CONTROL_SHADER);
    GLuint tesShader = createShader(tES, GL_TESS_EVALUATION_SHADER);
    GLuint gShader = createShader(gp, GL_GEOMETRY_SHADER);
    GLuint fShader = createShader(fp, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, tcShader);
    glAttachShader(program, tesShader);
    glAttachShader(program, gShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    checkOpenGLError();
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "Program linking failed!" << endl;
        printProgramLog(program);
        glDeleteProgram(program);
        program = 0;
    }
    glDeleteShader(vShader);
    glDeleteShader(tcShader);
    glDeleteShader(tesShader);
    glDeleteShader(gShader);
    glDeleteShader(fShader);
    return program;
}

GLuint Utils::loadTexture(const char *texImagePath) {
    GLuint textureID = SOIL_load_OGL_texture(
        texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureID == 0)
        cout << "Could not find texture file: " << texImagePath << endl;
    return textureID;
}

GLuint Utils::loadCubeMaps(const std::vector<std::string> &texFiles) {
    if (texFiles.size() != 6)
        throw string("Wrong number of texture files");
    GLuint textureID = SOIL_load_OGL_cubemap(
        texFiles[0].c_str(), texFiles[1].c_str(), texFiles[2].c_str(),
        texFiles[3].c_str(), texFiles[4].c_str(), texFiles[5].c_str(),
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}