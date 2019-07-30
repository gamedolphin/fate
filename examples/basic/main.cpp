#include <iostream>
#include "fate/core.h"
#include "fate/log.h"
#include "fate/gamestate.h"

using namespace Fate;

int main(int argc, char** argv) {

  GameState gameState;
  gameState.windowState = {
                           .windowTitle = "Hello",
                           .width = 400,
                           .height = 300
  };
  Game game;


  SceneConfig sceneConfig;
  sceneConfig.OnInitialize = [](GameState& state) {
                               Fate::LogMessage("Initializing game");
                             };
  int counter = 0;
  sceneConfig.OnUpdate = [&](GameState& state) {
                           if(counter++ >= 10) {
                             game.sceneManager.SetScene(state, 2);
                           }
                           Fate::LogMessage(std::to_string(counter));
                         };

  SceneConfig sceneConfig2;
  sceneConfig2.OnUpdate = [&](GameState& state) {
                            if(counter-- <= 0) {
                              state.isRunning = false;
                            }
                            Fate::LogMessage(std::to_string(counter));
                          };

  int sceneId = game.sceneManager.AddScene(gameState, sceneConfig);
  game.sceneManager.SetScene(gameState, sceneId);
  int sceneId2 = game.sceneManager.AddScene(gameState, sceneConfig2);
  Fate::LogMessage(std::to_string(sceneId));
  game.Run(gameState);
  return 0;
}
