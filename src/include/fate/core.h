#pragma once
#include "window.h"
#include "gamestate.h"
#include "input.h"
#include "renderer.h"

namespace Fate {

  class Game {
  public:
    WindowManager window;
    InputManager input;
    Renderer renderer;
    Game();
    void Run(GameState& state);
  };
};
