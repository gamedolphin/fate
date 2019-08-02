#include "fate/sprite.h"
#include <bgfx/bgfx.h>
#include <memory>

namespace Fate {

  void SpriteConstants::Initialize() {
    const uint16_t indices[6] =
      {
       0, 1, 2,
       2, 3, 0
      };

    const PosTexcoordVertex s_cubeVertices[] =
      {
       {-0.5f, -0.5f, 1, 1 },
       {-0.5f, 0.5f, 1, 0 },
       {0.5f, 0.5f, 0, 0 },
       {0.5f, -0.5f, 0, 1 }
      };

    bgfx::VertexDecl ms_decl;
    ms_decl
      .begin()
      .add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
      .end();

    textureUniform = std::make_shared<bgfx::UniformHandle>(bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler));
    indexBufferHandle = std::make_shared<bgfx::IndexBufferHandle>(bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(indices) ) ));
    vertexBufferHandle = std::make_shared<bgfx::VertexBufferHandle>
      (bgfx::createVertexBuffer
       (bgfx::makeRef
        (s_cubeVertices,
         sizeof(s_cubeVertices)),
        ms_decl
        ));
  }

  void SpriteConstants::Destroy() {
    bgfx::destroy(*textureUniform);
    bgfx::destroy(*vertexBufferHandle);
    bgfx::destroy(*indexBufferHandle);
  }
}
