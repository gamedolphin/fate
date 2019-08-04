#pragma once
#include <functional>
#include <memory>
#include <unordered_map>

namespace Fate {

  class Game;
  struct GameState;

  static std::function<void(GameState&)> noop = [](GameState& state) {};

  struct SceneConfig {
    std::function<void(GameState&)> OnInitialize = noop;
    std::function<void(GameState&)> OnUpdate = noop;
    std::function<void(GameState&)> OnShutdown = noop;
  };

  class Scene {
    friend class SceneManager;

    void Update(GameState& state);
    SceneConfig config;

    bool initialized = false;
  public:
    int sceneId;
    Scene(int id, SceneConfig _config) : config(_config), sceneId(id) {}
    void Shutdown(GameState& state);
  };

  struct SceneState {
    int currentSceneId = -1;
    std::unordered_map<int,Scene> sceneList = {};
  };

  class SceneManager {
    friend class Game;
    static void Update(GameState& gameState);
  };

  int AddScene(GameState& gameState, SceneConfig config, int sceneId);
  void SetScene(GameState& gameState, int sceneId);
};
