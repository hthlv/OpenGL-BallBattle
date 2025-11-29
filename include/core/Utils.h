//
// Created by htlix on 2025/10/23.
//
#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

using std::string;

class Utils {
public:
    static string readShaderSource(const char *filePath);
    static void printShaderLog(GLuint shader);
    static void printProgramLog(GLuint program);
    static bool checkOpenGLError();
    static GLuint createShaderProgram(const char *vsFilePath,
                                      const char *fsFilePath);
    static GLuint createShaderProgram(const char *vp, const char *gp,
                                      const char *fp);
    static GLuint createShaderProgram(const char *vp, const char *tCS,
                                      const char *tES, const char *fp);
    static GLuint createShaderProgram(const char *vp, const char *tCS,
                                      const char *tES, const char *gp,
                                      const char *fp);
    static GLuint loadTexture(const char *texImagePath);
    static GLuint loadCubeMaps(const std::vector<std::string> &texFiles);

private:
    static GLuint createShader(const char *shaderFilePath, GLenum shaderType);
};
