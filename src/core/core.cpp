#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"

namespace Fate {

  void Game::Initialize(GameState &state) {
    Window::CreateWindow(state.windowState);
    Renderer::InitializeRenderer(state.windowState, state.renderState, state.entityState);
  }

  void Game::Run(GameState& state) {
    state.isRunning = true;
    while(state.isRunning) {
      state.inputState = Input::ReadInput(state.inputState);
      if(state.inputState.eventType == EventType::QUIT) {
        state.isRunning = false;
        break;
      }
      SceneManager::Update(state);
      Renderer::Render(state.windowState, state.renderState, state.entityState);
    }

    UnloadAllResources(state.resourceState);
    Renderer::ShutdownRenderer(state.windowState, state.renderState);
    Window::ShutdownWindow(state.windowState);
  }

  void Game::StopGame(GameState &state) {
    state.isRunning = false;
  }
};
