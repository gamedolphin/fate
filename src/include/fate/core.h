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
    static void Initialize(GameState& state);
    static void Run(GameState& state);
    static void StopGame(GameState& state);
  };
};
