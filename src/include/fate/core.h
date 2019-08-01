#pragma once
#include "window.h"
#include "gamestate.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "resource.h"

namespace Fate {

  class Game {
  public:
    WindowManager window;
    InputManager input;
    Renderer renderer;
    SceneManager sceneManager;
    ResourceManager resourceManager;

    Game();
    void Initialize(GameState& state);
    void Run(GameState& state);
    void StopGame(GameState& state);
  };
};
