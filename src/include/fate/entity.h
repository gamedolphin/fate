#pragma once
#include <entt/entt.hpp>

namespace Fate {
  struct EntityState {
    entt::registry registry;
  };

  entt::entity CreateEntity(EntityState& state);
};
