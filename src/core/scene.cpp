#include "fate/scene.h"
#include "fate/core.h"

namespace Fate {

struct ActiveScene {};

void Scene::Update(GameState& state) {
  if (initialized == false) {
    config.OnInitialize(state, *this);
    initialized = true;
  }
  config.OnUpdate(state, *this);
}

void Scene::Shutdown(GameState& state) {
  config.OnShutdown(state, *this);
  initialized = false;
  auto& registry = state.entityState.registry;
  for (const auto entity : registry.view<ActiveScene>()) {
    registry.destroy(entity);
  }
}

entt::entity Scene::CreateEntity(GameState& state) {
  auto entity = Fate::CreateEntity(state.entityState);
  state.entityState.registry.assign<ActiveScene>(entity);
  return entity;
}

int Scenes::AddScene(GameState& gameState, SceneConfig config, int sceneId) {
  Scene scene(sceneId, config);
  gameState.sceneState.sceneList.insert(std::make_pair(sceneId, scene));
  return sceneId;
};

void Scenes::SetScene(GameState& gameState, int sceneId) {
  auto& sceneState = gameState.sceneState;
  if (sceneState.currentSceneId == sceneId) {
    return;
  }
  if (sceneState.sceneList.find(sceneId) != sceneState.sceneList.end()) {
    if (sceneState.currentSceneId != -1) {
      sceneState.sceneList.at(sceneState.currentSceneId).Shutdown(gameState);
    }

    sceneState.currentSceneId = sceneId;
  }
}

void Scenes::Update(GameState& gameState) {
  if (gameState.sceneState.currentSceneId == -1) {
    return;
  }

  auto& sceneState = gameState.sceneState;
  auto& scene = sceneState.sceneList.at(sceneState.currentSceneId);
  scene.Update(gameState);
}
}  // namespace Fate
