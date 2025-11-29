#include "core/ResourceManager.h"
#include "core/Shader.h"
#include "core/Texture2D.h"
#include <iostream>
#include <memory>

ResourceManager &ResourceManager::instance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadTexture(const std::string &name,
                                  const std::string &path) {
    if (name.empty() || path.empty()) {
        std::cerr << "Texture load failed, name or path is empty" << std::endl;
        return false;
    }
    this->m_textures[name] = std::make_shared<Texture2D>(path);
    return true;
}

bool ResourceManager::loadShader(const std::string &name, const std::string &vs,
                                 const std::string &fs) {
    if (name.empty() || vs.empty() || fs.empty()) {
        std::cerr << "Shader load failed, name, vertex or fragment is empty!"
                  << std::endl;
        return false;
    }
    this->m_shaders[name] = std::make_shared<Shader>(vs, fs);

    return true;
}

std::shared_ptr<Texture2D>
ResourceManager::getTexture(const std::string &name) {
    if (name.empty())
        return nullptr;
    auto it = m_textures.find(name);
    return (it != this->m_textures.end()) ? it->second : nullptr;
}
std::shared_ptr<Shader> ResourceManager::getShader(const std::string &name) {
    if (name.empty())
        return nullptr;
    auto it = this->m_shaders.find(name);
    return (it != this->m_shaders.end()) ? it->second : nullptr;
}