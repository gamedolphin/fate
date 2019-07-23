#pragma once
#include "window.h"
#include "gamestate.h"
#include "input.h"

namespace Fate {

  class Game {
  public:
    WindowManager window;
    InputManager input;
    Game();
    void Run(GameState& state);
  };
};
