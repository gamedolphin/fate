#pragma once
#include <memory>
#include "shader.h"

namespace bgfx {
  struct UniformHandle;
  struct VertexBufferHandle;
  struct IndexBufferHandle;
  struct ProgramHandle;
}

namespace Fate {

  struct PosTexcoordVertex
  {
    float m_x;
    float m_y;
    float m_u;
    float m_v;
  };

  struct SpriteConstants {
    bool setup = false;
    std::shared_ptr<bgfx::ProgramHandle> programHandle;
    std::shared_ptr<bgfx::UniformHandle> textureUniform;
    std::shared_ptr<bgfx::VertexBufferHandle> vertexBufferHandle;
    std::shared_ptr<bgfx::IndexBufferHandle> indexBufferHandle;
  };

  void InitializeSpriteRenderProperties(ShaderState &shaderState, SpriteConstants &spriteConstants);
  void DestroySpriteRenderProperties(SpriteConstants &spriteConstants);
}
