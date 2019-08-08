#pragma once
#include <chrono>

using namespace std::chrono_literals;

namespace Fate {

  typedef std::chrono::duration<long, std::ratio<1,1000000000>> Duration;
  typedef std::chrono::time_point<std::chrono::high_resolution_clock, Duration> TimePoint;

  struct GameState;

  struct TimeState {
    int targetFPS = 60;
    Duration deltaTime;
    TimePoint startTime;
    TimePoint frameTimeStart;
    std::chrono::nanoseconds timestep;
    std::chrono::nanoseconds lag = std::chrono::nanoseconds(0ns);
  };

  class Time {
    friend class Game;
    static void Initialize(TimeState& state);
    static void FrameStart(TimeState& state);

  public:
    static float GetDeltaTime(GameState& state);
  };
}
