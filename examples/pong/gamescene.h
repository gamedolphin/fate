#pragma once
#include <fate/gamestate.h>

namespace Pong {
struct Paddle {};
struct Velocity {
  float x, y;
};

class GameScene {
  void ProcessInput(Fate::GameState& state, entt::entity& player);
  void UpdatePositions(Fate::GameState& state);
  void ProcessPaddles(Fate::GameState& state);
  Fate::RenderSize paddleSize;
  float paddleSpeed = 10;
  entt::entity playerPaddle;

 public:
  Fate::SceneConfig sceneConfig;
  GameScene(Fate::GameState& gameState);
};

};  // namespace Pong
