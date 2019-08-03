#pragma once

namespace Fate {

  enum class EventType { NONE, QUIT };

  struct InputState {
    EventType eventType = EventType::NONE;
  };

  class Input {
  public:
    static InputState& ReadInput(InputState& inputState);
  };
};
