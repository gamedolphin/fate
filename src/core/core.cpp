#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"
#include "fate/time.h"

namespace Fate {

  void Game::Initialize(GameState &state) {
    Window::CreateWindow(state.windowState);
    Renderer::InitializeRenderer(state.windowState, state.renderState, state.entityState);
  }

  void Game::Run(GameState& state) {
    state.isRunning = true;

    Time::Initialize(state.timeState);

    while(state.isRunning) {

      Time::FrameStart(state.timeState);

      Input::ReadInput(state.inputState);

      if(state.inputState.eventType == EventType::QUIT) {
        StopGame(state);
        break;
      }

      while(Time::HasLag(state.timeState)) {
        Time::Update(state.timeState);
        // busy wait
      }

      Scenes::Update(state);
      Renderer::Render(state.windowState, state.renderState, state.entityState);
    }

    Resources::UnloadAllResources(state);
    Renderer::ShutdownRenderer(state.windowState, state.renderState);
    Window::ShutdownWindow(state.windowState);
  }

  void Game::StopGame(GameState &state) {
    state.isRunning = false;
  }
};
