#pragma once
#include "math.h"

namespace Fate {

  struct Position : Vector3  { };

  struct Rotation : Vector3 { };

  struct Scale : Vector3 { };

  struct Transform {
    Position position;
    Rotation rotation;
    Scale scale;

    bool isDirty = true;
    float mtx[16];
  };

  Transform& SetTransformX(Transform &transform, float x) {
    transform.position.x = x;
    transform.isDirty = true;
    return transform;
  }

  Transform& SetTransformXY(Transform &transform, float x, float y) {
    transform.position.x = x;
    transform.position.y = y;
    transform.isDirty = true;
    return transform;
  }
}
