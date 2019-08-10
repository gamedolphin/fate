#include <fate/core.h>
#include <fate/gamestate.h>
#include <fate/log.h>
#include "gamescene.h"

int main(int argc, char** argv) {
  Fate::GameState gameState;
  gameState.windowState = {
      .windowTitle = "Pong Game", .width = 800, .height = 600};

  Fate::Game::Initialize(gameState);

  auto gameScene = Pong::GameScene(gameState);

  auto sceneId = Fate::Scenes::AddScene(gameState, gameScene.sceneConfig, 0);
  Fate::Scenes::SetScene(gameState, sceneId);

  Fate::Game::Run(gameState);

  return 0;
}
