#pragma once
#include "gamestate.h"
#include "input.h"
#include "renderer.h"
#include "resource.h"
#include "scene.h"
#include "window.h"

namespace Fate {

class Game {
 public:
  static void Initialize(GameState& state);
  static void Run(GameState& state);
  static void StopGame(GameState& state);
};
};  // namespace Fate
