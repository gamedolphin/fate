#include "fate/random.h"

namespace Fate {
namespace Random {

float get() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(0.0, 1.0);
  return dist(mt);
}

float get(float min, float max) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(min, max);
  return dist(mt);
}

}  // namespace Random
};  // namespace Fate
