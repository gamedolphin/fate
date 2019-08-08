#pragma once
#include "window.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "entity.h"
#include "resource.h"
#include "time.h"

namespace Fate {

  struct GameState {
    bool isRunning = false;
    WindowState windowState;
    InputState inputState;
    RenderState renderState;
    SceneState sceneState;
    EntityState entityState;
    ResourceState resourceState;
    TimeState timeState;
  };
}
