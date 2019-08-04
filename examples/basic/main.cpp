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

  Fate::LoadTexture(gameState.resourceState,"textures/FATE.png", "Fate");

  auto entity = Fate::CreateEntity(gameState.entityState);
  auto sprite = Fate::MakeSprite(entity,
                                 gameState.entityState.registry,
                                 gameState.resourceState,
                                 "Fate");

  Fate::SceneConfig sceneConfig;
  sceneConfig.OnInitialize = [](Fate::GameState& state) {
                               Fate::LogMessage("Initializing game");
                             };
  int counter = 0;
  sceneConfig.OnUpdate = [&](Fate::GameState& state) {
                           if(++counter >= 10) {
                             Fate::SetScene(state, 1);
                           }
                           Fate::LogMessage(std::to_string(counter));
                         };
  int sceneId = Fate::AddScene(gameState, sceneConfig, 0);

  Fate::SceneConfig sceneConfig2;
  sceneConfig2.OnUpdate = [&](Fate::GameState& state) {
                            if(--counter <= 0) {
                              Fate::Game::StopGame(state);
                            }
                            Fate::LogMessage(std::to_string(counter));
                          };

  int sceneId2 = Fate::AddScene(gameState, sceneConfig2, 1);

  Fate::SetScene(gameState, sceneId);

  Fate::Game::Run(gameState);

  return 0;
}
