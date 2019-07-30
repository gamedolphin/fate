#pragma once
#include "window.h"
#include "shader.h"

namespace Fate {

  struct RenderState {

  };

  class Renderer {
    ShaderManager shaderManager;
  public:
    void InitializeRenderer(WindowState& windowState, RenderState& renderState);
    void Render(WindowState& windowState, RenderState& renderState);
    void ShutdownRenderer(WindowState& windowState, RenderState& renderState);
    ~Renderer();
  };
};
