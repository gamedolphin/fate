#pragma once
#include <entt/entt.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace bgfx {
  struct TextureHandle;
}

namespace Fate {

  struct GameState;

  struct ResourceState {
    std::unordered_map<entt::hashed_string::hash_type,std::shared_ptr<bgfx::TextureHandle>> textures = {};
  };

  class Resources {
    friend class Game;
    static void UnloadAllResources(GameState &state);
    Resources();
  public:
    static void LoadTexture(GameState& state, std::string fileName, std::string name);
    static void LoadTexture(ResourceState& state, std::string fileName, std::string name);
  };
}
