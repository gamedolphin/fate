#pragma once
#include <cstdint>
#include "math.h"

namespace Fate {
  struct CameraComponent {
    uint8_t viewId;
    float fov;
    float aspectRatio;
    float near;
    float far;
    Rect viewPort; // { 0, 0 , 1, 1 } relative to window
  };
};
