#pragma once
#include "window.h"
#include "shader.h"
#include "entity.h"

namespace Fate {

  struct RenderState {

  };

  class Renderer {
    ShaderManager shaderManager;
  public:
    void InitializeRenderer(WindowState& windowState, RenderState& renderState, EntityState& entityState);
    void Render(WindowState& windowState, RenderState& renderState, EntityState &entityState);
    void ShutdownRenderer(WindowState& windowState, RenderState& renderState);
    ~Renderer();
  };
};
