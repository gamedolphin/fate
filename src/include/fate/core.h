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
    SceneManager sceneManager;

    void Initialize(GameState& state);
    void Run(GameState& state);
    void StopGame(GameState& state);
  };
};
