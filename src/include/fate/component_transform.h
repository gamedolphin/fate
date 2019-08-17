#pragma once
#include "math.h"

namespace Fate {

struct Transform {
  Vector3 position;
  Vector3 rotation;
  Vector3 scale = {1, 1, 1};

  bool isDirty = true;
};

struct TransformMatrix {
  float mtx[16];
};

Transform& SetTransformX(Transform& transform, float x) {
  transform.position.x = x;
  transform.isDirty = true;
  return transform;
}

Transform& SetTransformXY(Transform& transform, float x, float y) {
  transform.position.x = x;
  transform.position.y = y;
  transform.isDirty = true;
  return transform;
}
}  // namespace Fate
