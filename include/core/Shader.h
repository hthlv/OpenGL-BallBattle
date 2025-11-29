//
// Created by htlix on 2025/10/29.
//

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader();
    Shader(const char *vp, const char *fp);
    Shader(const char *vp, const char *gp, const char *fp);
    Shader(const char *vp, const char *tCS, const char *tES, const char *fp);
    Shader(const char *vp, const char *tCS, const char *tES, const char *gp,
           const char *fp);
    Shader(const std::string &vp, const std::string &fp);
    Shader(const std::string &vp, const std::string &gp, const std::string &fp);
    Shader(const std::string &vp, const std::string &tCS,
           const std::string &tES, const std::string &fp);
    Shader(const std::string &vp, const std::string &tCS,
           const std::string &tES, const std::string &gp,
           const std::string &fp);
    ~Shader();

    Shader &use();
    GLuint getProgramID() const;

    // 设置值
    void setInt(const std::string &name, int value);

    void setFloat(const char *name, const float &value);
    void setFloat(const std::string &name, const float &value);

    void setVec2(const char *name, const glm::vec2 &value);
    void setVec2(const char *name, const float &x, const float &y);
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec2(const std::string &name, const float &x, const float &y);

    void setVec3(const char *name, const glm::vec3 &value);
    void setVec3(const char *name, const float &x, const float &y,
                 const float &z);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec3(const std::string &name, const float &x, const float &y,
                 const float &z);

    void setVec4(const char *name, const glm::vec4 &value);
    void setVec4(const char *name, const float &x, const float &y,
                 const float &z, const float &w);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setVec4(const std::string &name, const float &x, const float &y,
                 const float &z, const float &w);

    void setMat4(const char *name, const glm::mat4 &matrix);
    void setMat4(const std::string &name, const glm::mat4 &matrix);

private:
    GLuint programID;
};

#endif // SHADER_H