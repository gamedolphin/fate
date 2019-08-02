#pragma once
#include <memory>

namespace bgfx {
  struct UniformHandle;
  struct VertexBufferHandle;
  struct IndexBufferHandle;
}

namespace Fate {
  class SpriteConstants {
    struct PosTexcoordVertex
    {
      float m_x;
      float m_y;
      float m_u;
      float m_v;
    };

  public:
    std::shared_ptr<bgfx::UniformHandle> textureUniform;
    std::shared_ptr<bgfx::VertexBufferHandle> vertexBufferHandle;
    std::shared_ptr<bgfx::IndexBufferHandle> indexBufferHandle;

    void Initialize();
    void Destroy();
  };
}
