#include <iostream>
#include "fate/core.h"
#include "fate/log.h"
#include "fate/gamestate.h"

using namespace Fate;

int main(int argc, char** argv) {

  GameState gameState;
  gameState.windowState = {
                           .windowTitle = "Sprite Test",
                           .width = 800,
                           .height = 600
  };
  Game game;
  game.Initialize(gameState);

  Fate::LoadTexture(gameState.resourceState,"textures/FATE.png", "Fate");

  auto entity = Fate::CreateEntity(gameState.entityState);
  auto sprite = Fate::MakeSprite(entity,
                                 gameState.entityState.registry,
                                 gameState.resourceState,
                                 "Fate");

  // SceneConfig sceneConfig;
  // sceneConfig.OnInitialize = [](GameState& state) {
  //                              Fate::LogMessage("Initializing game");
  //                            };
  // int counter = 0;
  // sceneConfig.OnUpdate = [&](GameState& state) {
  //                          if(++counter >= 10) {
  //                            game.sceneManager.SetScene(state, 1);
  //                          }
  //                          Fate::LogMessage(std::to_string(counter));
  //                        };
  // int sceneId = game.sceneManager.AddScene(gameState, sceneConfig, 0);

  // SceneConfig sceneConfig2;
  // sceneConfig2.OnUpdate = [&](GameState& state) {
  //                           if(--counter <= 0) {
  //                             game.StopGame(state);
  //                           }
  //                           Fate::LogMessage(std::to_string(counter));
  //                         };

  // int sceneId2 = game.sceneManager.AddScene(gameState, sceneConfig2, 1);

  // game.sceneManager.SetScene(gameState, sceneId);

  game.Run(gameState);

  return 0;
}
