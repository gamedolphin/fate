#pragma once
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include "component_render.h"

namespace bgfx {
struct TextureHandle;
}

namespace Fate {

struct GameState;

struct ResourceState {
  std::unordered_map<entt::hashed_string::hash_type, TextureResource> textures =
      {};
};

class Resources {
  friend class Game;
  static void UnloadAllResources(GameState& state);
  Resources();

 public:
  static void LoadTexture(GameState& state, std::string fileName,
                          std::string name);
  static void LoadTexture(ResourceState& state, std::string fileName,
                          std::string name);
  static RenderSize GetTextureSize(GameState& state, std::string textureName);
};
}  // namespace Fate
