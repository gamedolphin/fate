#include "fate/time.h"
#include "fate/gamestate.h"
#include <chrono>

namespace Fate {

  using namespace std::chrono_literals;
  typedef std::chrono::duration<float, std::milli> fsec;

  void Time::Initialize(TimeState &state) {
    using clock = std::chrono::high_resolution_clock;
    state.timestep = std::chrono::nanoseconds(16ms);
    state.startTime = clock::now();
    state.frameTimeStart = clock::now();
  };

  void Time::FrameStart(TimeState& state) {
    using clock = std::chrono::high_resolution_clock;
    auto frameTime = clock::now();
    state.deltaTime =  frameTime - state.frameTimeStart;
    state.frameTimeStart = frameTime;
    state.lag += std::chrono::duration_cast<std::chrono::nanoseconds>(state.deltaTime);
  }

  bool Time::HasLag(TimeState& state) {
    return state.lag >= state.timestep;
  };

  void Time::Update(TimeState& state) {
    state.lag -= state.timestep;
  };

  float Time::GetDeltaTime(GameState &state) {
    fsec fs = state.timeState.deltaTime;
    return (float)fs.count()/1000;
  };
};
