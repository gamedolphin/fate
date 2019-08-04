#include <iostream>
#include "fate/core.h"
#include "fate/log.h"
#include "fate/gamestate.h"

int main(int argc, char** argv) {

  Fate::GameState gameState;
  gameState.windowState = {
                           .windowTitle = "Sprite Test",
                           .width = 800,
                           .height = 600
  };

  Fate::Game::Initialize(gameState);
  Fate::Resources::LoadTexture(gameState,"textures/FATE.png", "Fate");

  Fate::SceneConfig sceneConfig;
  sceneConfig.OnInitialize = [](Fate::GameState& state, Fate::Scene& scene) {
                               Fate::LogMessage("Initializing game");

                               auto entity = scene.CreateEntity(state);
                               auto sprite = Fate::Renderer::MakeSprite(entity,
                                                                        state,
                                                                        "Fate");
                             };

  sceneConfig.OnUpdate = [&](Fate::GameState& state, Fate::Scene& scene) {
                         };


  int sceneId = Fate::Scenes::AddScene(gameState, sceneConfig, 0);

  Fate::Scenes::SetScene(gameState, sceneId);

  Fate::Game::Run(gameState);

  return 0;
}
