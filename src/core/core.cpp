#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"

namespace Fate {

  Game::Game() {

  }

  void Game::Initialize(GameState &state) {
    window.CreateWindow(state.windowState);
    renderer.InitializeRenderer(this, state.windowState, state.renderState, state.entityState);
  }

  void Game::Run(GameState& state) {
    state.isRunning = true;
    while(state.isRunning) {
      state.inputState = input.ReadInput(state.inputState);
      if(state.inputState.eventType == EventType::QUIT) {
        state.isRunning = false;
        break;
      }
      sceneManager.Update(state);
      renderer.Render(state.windowState, state.renderState, state.entityState);
    }

    renderer.ShutdownRenderer(state.windowState, state.renderState);
    window.ShutdownWindow(state.windowState);
  }

  void Game::StopGame(GameState &state) {
    state.isRunning = false;
  }
};
