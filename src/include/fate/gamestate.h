#pragma once
#include "window.h"
#include "input.h"

namespace Fate {

  struct GameState {
    bool isRunning = false;
    WindowState windowState;
    InputState inputState;
  };
}
