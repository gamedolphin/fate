#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"

namespace Fate {

  Game::Game() {

  }

  void Game::Run(GameState& state) {
    window.CreateWindow(state.windowState);

    state.isRunning = true;

    while(state.isRunning) {
      state.inputState = input.ReadInput(state.inputState);
      if(state.inputState.eventType == EventType::QUIT) {
        state.isRunning = false;
      }
    }
  }
};
