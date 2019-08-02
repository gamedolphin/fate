#pragma once
#include <cstdint>
#include <string>
#include <entt/entt.hpp>

namespace bgfx {
  struct TextureHandle;
  struct ProgramHandle;
}

namespace Fate {

  enum class RenderType
    {
     NONE,
     SPRITE
    };

  struct RenderComponent {
    uint8_t vertexBufferId;
    uint8_t indexBufferId;
    std::shared_ptr<bgfx::ProgramHandle> programHandle;
    RenderType type;
  };

  struct RenderSize {
    float width;
    float height;
  };

  struct Sprite : RenderComponent {
    std::shared_ptr<bgfx::TextureHandle> texture;
    RenderSize size;
  };
};
