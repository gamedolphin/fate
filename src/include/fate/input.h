#pragma once
#include <unordered_map>

namespace Fate {

enum class EventType { NONE, QUIT, KEY_UP, KEY_DOWN };

enum class KeyCode { NONE, W, A, S, D, LEFT, RIGHT, UP, DOWN, SPACE };

struct KeyboardState {
  std::unordered_map<KeyCode, bool> keys;
};

struct QuitState {};

struct InputState {
  EventType eventType = EventType::NONE;
  KeyboardState keyboardState;
};

class Input {
 public:
  static InputState& ReadInput(InputState& inputState);
  const static bool IsKeyPressed(const KeyboardState& state, KeyCode key);
};
};  // namespace Fate
