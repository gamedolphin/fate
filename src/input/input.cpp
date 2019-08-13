#include "fate/input.h"
#include <SDL2/SDL.h>
#include "fate/log.h"

namespace Fate {
SDL_Event eventBox;

KeyCode GetKey(SDL_Keycode key) {
  switch (key) {
    case SDLK_w:
      return KeyCode::W;
    case SDLK_a:
      return KeyCode::A;
    case SDLK_s:
      return KeyCode::S;
    case SDLK_d:
      return KeyCode::D;
    case SDLK_SPACE:
      return KeyCode::SPACE;
  }

  return KeyCode::NONE;
}

void UpdateKeyboardState(KeyboardState& keyboardState, SDL_Keycode key,
                         bool state) {
  auto inputKey = GetKey(key);
  if (inputKey != KeyCode::NONE) {
    keyboardState.keys.insert_or_assign(inputKey, state);
  }
}

InputState& Input::ReadInput(InputState& inputState) {
  while (SDL_PollEvent(&eventBox) != 0) {
    switch (eventBox.type) {
      case SDL_QUIT:
        inputState.eventType = EventType::QUIT;
        break;
      case SDL_KEYUP:
        inputState.eventType = EventType::KEY_UP;
        UpdateKeyboardState(inputState.keyboardState, eventBox.key.keysym.sym,
                            false);
        break;
      case SDL_KEYDOWN:
        inputState.eventType = EventType::KEY_DOWN;
        UpdateKeyboardState(inputState.keyboardState, eventBox.key.keysym.sym,
                            true);
        break;
      default:
        inputState.eventType = EventType::NONE;
        break;
    }
  }

  return inputState;
}

const bool Input::IsKeyPressed(const KeyboardState& state, KeyCode key) {
  auto k = state.keys.find(key);
  if (k == state.keys.end()) {
    return false;
  }
  return k->second;
};
};  // namespace Fate
