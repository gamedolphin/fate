#pragma once
#include <cstdint>
#include <string>

namespace Fate {

  enum class RenderType
    {
     NONE,
     SPRITE
    };

  struct RenderComponent {
    uint8_t vertexBufferId;
    uint8_t indexBufferId;
    uint8_t programId;
    RenderType type;
  };

  struct RenderSize {
    float width;
    float height;
  };

  struct Sprite : RenderComponent {
    std::string textureId;
    RenderSize size;
  };
};
