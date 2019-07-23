#include "fate/input.h"
#include <SDL2/SDL.h>

namespace Fate {
  SDL_Event eventBox;

  InputState& InputManager::ReadInput(InputState &inputState) {
    bool hasInput = SDL_PollEvent(&eventBox);

    switch(eventBox.type) {
    case SDL_QUIT:
      inputState.eventType = EventType::QUIT;
      break;
    default:
      inputState.eventType = EventType::NONE;
      break;
    }

    return inputState;
  }
};
