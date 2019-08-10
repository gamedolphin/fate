#pragma once
#include <cstdint>
#include <entt/entt.hpp>
#include <string>

namespace bgfx {
struct TextureHandle;
struct ProgramHandle;
}  // namespace bgfx

namespace Fate {

struct RenderSize {
  uint32_t width;
  uint32_t height;
};

enum class RenderType { NONE, SPRITE };

struct TextureResource {
  std::shared_ptr<bgfx::TextureHandle> textureHandle;
  RenderSize size;
};

struct RenderComponent {
  uint8_t vertexBufferId;
  uint8_t indexBufferId;
  std::shared_ptr<bgfx::ProgramHandle> programHandle;
  RenderType type;
};

struct Sprite {
  TextureResource texture;
};
};  // namespace Fate
