#include "fate/entity.h"

namespace Fate {

  entt::entity CreateEntity(EntityState &state) {
    auto entity = state.registry.create();
    return entity;
  };
}
