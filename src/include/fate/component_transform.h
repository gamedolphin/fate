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
  };
}
