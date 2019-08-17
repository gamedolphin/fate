#include "fate/core.h"
#include "fate/gamestate.h"
#include "fate/log.h"
#include "fate/time.h"

namespace Fate {

void Game::Run(GameState &state) {
  state.isRunning = true;

  Window::CreateWindow(state.windowState);
  Time::Initialize(state.timeState);

  Renderer::StartRenderer(state);

  while (state.isRunning) {
    Time::FrameStart(state.timeState);

    Input::ReadInput(state.inputState);

    if (state.inputState.eventType == EventType::QUIT) {
      StopGame(state);
      break;
    }

    while (state.timeState.lag >= state.timeState.timestep) {
      state.timeState.lag -= state.timeState.timestep;
      // busy wait
    }

    Scenes::Update(state);
  }

  Resources::UnloadAllResources(state);
  Renderer::ShutdownRenderer(state);
  Window::ShutdownWindow(state.windowState);
}

void Game::StopGame(GameState &state) { state.isRunning = false; }
};  // namespace Fate
