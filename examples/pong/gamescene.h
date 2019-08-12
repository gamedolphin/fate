#pragma once
#include <fate/gamestate.h>

namespace Pong {

class GameScene {
  entt::entity playerPaddle;
  entt::entity ball;

 public:
  Fate::SceneConfig sceneConfig;
  GameScene(Fate::GameState& gameState);
};

};  // namespace Pong
