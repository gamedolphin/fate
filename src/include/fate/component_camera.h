#pragma once
#include <cstdint>
#include "math.h"

namespace Fate {

enum class CameraType { ORTHOGRAPHIC, PERSPECTIVE };

struct CameraComponent {
  uint8_t viewId;
  float fov;
  float aspectRatio;
  float near;
  float far;
  Rect viewPort;  // { 0, 0 , 1, 1 } relative to window
  float orthoSize = 1000;
  CameraType cameraType = CameraType::ORTHOGRAPHIC;
  float projectionMatrix[16];
  bool dirty = true;
};
};  // namespace Fate
