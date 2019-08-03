#pragma once
#include <entt/entt.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace bgfx {
  struct TextureHandle;
}

namespace Fate {

  struct ResourceState {
    std::unordered_map<entt::hashed_string::hash_type,std::shared_ptr<bgfx::TextureHandle>> textures = {};
  };

  void LoadTexture(ResourceState& state, std::string fileName, std::string name);

  void UnloadAllResources(ResourceState &state);

}
