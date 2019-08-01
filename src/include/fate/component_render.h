#pragma once
#include <cstdint>

namespace Fate {

  struct RenderComponent {
    uint8_t vertexBufferId;
    uint8_t indexBufferId;
    uint8_t programId;
  };

  struct RenderSize {
    float width;
    float height;
  };

  struct Sprite : RenderComponent {
    uint8_t textureId;
    RenderSize size;
  };
};
