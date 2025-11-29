#pragma once
#include "core/Shader.h"
#include "core/Texture2D.h"
#include <memory>
#include <string>
#include <unordered_map>
class ResourceManager {
public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    static ResourceManager &instance();

    // 资源加载接口
    bool loadTexture(const std::string &name, const std::string &path);
    bool loadShader(const std::string &name, const std::string &vs,
                    const std::string &fs);

    std::shared_ptr<Texture2D> getTexture(const std::string &name);
    std::shared_ptr<Shader> getShader(const std::string &name);

private:
    ResourceManager() = default;
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_textures;
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};