#pragma once

namespace Fate {

  enum class EventType { NONE, QUIT };

  struct InputState {
    EventType eventType = EventType::NONE;
  };

  class InputManager {
  public:
    InputState& ReadInput(InputState& inputState);
  };
};
