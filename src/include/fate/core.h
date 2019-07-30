#pragma once
#include "window.h"
#include "gamestate.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"

namespace Fate {

  class Game {
  public:
    WindowManager window;
    InputManager input;
    Renderer renderer;
    SceneManager sceneManager;
    Game();
    void Run(GameState& state);
  };
};
