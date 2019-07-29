#pragma once
#include "window.h"

namespace Fate {

  struct RenderState {

  };

  class Renderer {

  public:
    void InitializeRenderer(WindowState& windowState, RenderState& renderState);
    ~Renderer();
  };
};
