#include "fate/core.h"
#include "fate/scene.h"

namespace Fate {

  void Scene::Update(GameState& state) {
    if(initialized == false) {
      config.OnInitialize(state);
      initialized = true;
    }
    config.OnUpdate(state);
  }

  void Scene::Shutdown(GameState& state) {
    config.OnShutdown(state);
    initialized = false;
  }

  int SceneManager::AddScene(GameState &gameState, SceneConfig config) {
    Scene scene(uKey,config);
    uKey = uKey + 1;
    gameState.sceneState.sceneList.insert(std::make_pair(uKey, scene));
    return uKey;
  };

  int SceneManager::AddScene(GameState &gameState, SceneConfig config, int sceneId) {
    Scene scene(uKey,config);
    gameState.sceneState.sceneList.insert(std::make_pair(sceneId, scene));
    if(sceneId >= uKey) {
      uKey = sceneId + 1;
    }
    return sceneId;
  };

  void SceneManager::SetScene(GameState& gameState, int sceneId) {
    auto &sceneState = gameState.sceneState;
    if(sceneState.currentSceneId == sceneId) {
      return;
    }
    if(sceneState.sceneList.find(sceneId) != sceneState.sceneList.end()) {

      if(sceneState.currentSceneId != -1) {
        sceneState.sceneList.at(sceneState.currentSceneId).Shutdown(gameState);
      }

      sceneState.currentSceneId = sceneId;
    }
  }

  void SceneManager::Update(GameState &gameState) {
    if(gameState.sceneState.currentSceneId == -1) {
      return;
    }

    auto& sceneState = gameState.sceneState;
    auto& scene = sceneState.sceneList.at(sceneState.currentSceneId);
    scene.Update(gameState);
  }
}
