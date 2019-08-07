#include "fate/sprite.h"
#include <bgfx/bgfx.h>
#include <memory>

namespace Fate {

  static constexpr uint16_t indices[6] =
      {
       3, 2, 1,
       3, 1, 0
      };

  static constexpr const PosTexcoordVertex s_cubeVertices[] =
      {
       { 0.5f,  0.5f, 1, 0 },
       { 0.5f, -0.5f, 1, 1 },
       {-0.5f, -0.5f, 0, 1 },
       {-0.5f,  0.5f, 0, 0 }
      };

  // static constexpr const PosTexcoordVertex s_cubeVertices[] =
  //     {
  //      {-0.5f, -0.5f, 0, 0 },
  //      {-0.5f,  0.5f, 0, 1 },
  //      {0.5f,   0.5f, 1, 1 },
  //      {0.5f,  -0.5f, 1, 0 }
  //     };

  void InitializeSpriteRenderProperties(ShaderState& shaderState,
                                        SpriteConstants &spriteConstants) {
    if(spriteConstants.setup == true) return;

    bgfx::VertexDecl ms_decl;
    ms_decl
      .begin()
      .add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
      .end();

    spriteConstants.textureUniform = std::make_shared<bgfx::UniformHandle>(bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler));
    spriteConstants.indexBufferHandle = std::make_shared<bgfx::IndexBufferHandle>(bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices) ) ));
    spriteConstants.vertexBufferHandle = std::make_shared<bgfx::VertexBufferHandle>
      (bgfx::createVertexBuffer
       (bgfx::makeRef
        (s_cubeVertices,
         sizeof(s_cubeVertices)),
        ms_decl
        ));

    auto programId = entt::hashed_string{"sprite"};
    spriteConstants.programHandle = shaderState.programs.at(programId);
  }

  void DestroySpriteRenderProperties(SpriteConstants &spriteConstants) {
    bgfx::destroy(*spriteConstants.textureUniform);
    bgfx::destroy(*spriteConstants.vertexBufferHandle);
    bgfx::destroy(*spriteConstants.indexBufferHandle);
  }
}
