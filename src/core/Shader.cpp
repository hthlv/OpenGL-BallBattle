//
// Created by htlix on 2025/10/29.
//

#include "core/Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "core/Utils.h"

Shader::Shader() {}

Shader::Shader(const char *vp, const char *fp) {
    programID = Utils::createShaderProgram(vp, fp);
}

Shader::Shader(const char *vp, const char *gp, const char *fp) {
    programID = Utils::createShaderProgram(vp, gp, fp);
}

Shader::Shader(const char *vp, const char *tCS, const char *tES,
               const char *fp) {
    programID = Utils::createShaderProgram(vp, tCS, tES, fp);
}

Shader::Shader(const char *vp, const char *tCS, const char *tES, const char *gp,
               const char *fp) {
    programID = Utils::createShaderProgram(vp, tCS, tES, gp, fp);
}

Shader::Shader(const std::string &vp, const std::string &fp) {
    programID = Utils::createShaderProgram(vp.c_str(), fp.c_str());
}

Shader::Shader(const std::string &vp, const std::string &gp,
               const std::string &fp) {
    programID = Utils::createShaderProgram(vp.c_str(), gp.c_str(), fp.c_str());
}

Shader::Shader(const std::string &vp, const std::string &tCS,
               const std::string &tES, const std::string &fp) {
    programID = Utils::createShaderProgram(vp.c_str(), tCS.c_str(), tES.c_str(),
                                           fp.c_str());
}

Shader::Shader(const std::string &vp, const std::string &tCS,
               const std::string &tES, const std::string &gp,
               const std::string &fp) {
    programID = Utils::createShaderProgram(vp.c_str(), tCS.c_str(), tES.c_str(),
                                           gp.c_str(), fp.c_str());
}

Shader::~Shader() {
    if (programID != 0) {
        std::cout << "Deleting shader program: " << programID << std::endl;
        glDeleteProgram(programID);
        programID = 0;
    }
}

Shader &Shader::use() {
    // std::cout << "Attempting to use shader program: " << programID <<
    // std::endl;
    //
    // // 检查程序是否存在
    // GLint isProgram;
    // glGetProgramiv(programID, GL_DELETE_STATUS, &isProgram);
    // if (isProgram == GL_TRUE) {
    //     std::cout << "ERROR: Shader program " << programID << " is marked for
    //     deletion!" << std::endl;
    // }

    glUseProgram(programID);

    // // 检查是否使用成功
    // GLint currentProgram;
    // glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    // std::cout << "After glUseProgram, current program: " << currentProgram <<
    // std::endl;
    //
    // if (currentProgram != static_cast<GLint>(programID)) {
    //     std::cout << "ERROR: Failed to activate shader program!" <<
    //     std::endl;
    //
    //     // 检查OpenGL错误
    //     GLenum error = glGetError();
    //     if (error != GL_NO_ERROR) {
    //         std::cout << "OpenGL error: " << error << std::endl;
    //     }
    // }

    return *this;
}

GLuint Shader::getProgramID() const { return programID; }

void Shader::setInt(const std::string &name, int value) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1i(loc, value);
}

void Shader::setFloat(const char *name, const float &value) {
    GLint loc = glGetUniformLocation(programID, name);
    glUniform1f(loc, value);
}

void Shader::setFloat(const std::string &name, const float &value) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform1f(loc, value);
}

void Shader::setVec2(const char *name, const glm::vec2 &value) {
    GLint loc = glGetUniformLocation(programID, name);
    glUniform2f(loc, value.x, value.y);
}

void Shader::setVec2(const char *name, const float &x, const float &y) {
    setVec2(name, glm::vec2(x, y));
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform2f(loc, value.x, value.y);
}

void Shader::setVec2(const std::string &name, const float &x, const float &y) {
    setVec2(name, glm::vec2(x, y));
}

void Shader::setVec3(const char *name, const glm::vec3 &value) {
    GLint loc = glGetUniformLocation(programID, name);
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setVec3(const char *name, const float &x, const float &y,
                     const float &z) {
    setVec3(name, glm::vec3(x, y, z));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setVec3(const std::string &name, const float &x, const float &y,
                     const float &z) {
    setVec3(name, glm::vec3(x, y, z));
}

void Shader::setVec4(const char *name, const glm::vec4 &value) {
    GLint loc = glGetUniformLocation(programID, name);
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setVec4(const char *name, const float &x, const float &y,
                     const float &z, const float &w) {
    setVec4(name, glm::vec4(x, y, z, w));
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setVec4(const std::string &name, const float &x, const float &y,
                     const float &z, const float &w) {
    setVec4(name, glm::vec4(x, y, z, w));
}

void Shader::setMat4(const char *name, const glm::mat4 &matrix) {
    GLint loc = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}