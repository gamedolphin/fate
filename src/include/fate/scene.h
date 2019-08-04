#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <entt/entt.hpp>

namespace Fate {

  class Game;
  class Scene;
  struct GameState;

  static std::function<void(GameState&, Scene& scene)> noop = [](GameState& state, Scene& scene) {};

  struct SceneConfig {
    std::string tag;
    std::function<void(GameState&, Scene&)> OnInitialize = noop;
    std::function<void(GameState&, Scene&)> OnUpdate = noop;
    std::function<void(GameState&, Scene&)> OnShutdown = noop;
  };

  class Scene {
    friend class Scenes;

    void Update(GameState& state);
    SceneConfig config;

    bool initialized = false;
  public:
    int sceneId;
    Scene(int id, SceneConfig _config) : config(_config), sceneId(id) { }
    void Shutdown(GameState& state);
    entt::entity CreateEntity(GameState& state);
  };

  struct SceneState {
    int currentSceneId = -1;
    std::unordered_map<int,Scene> sceneList = {};
  };

  class Scenes {
    friend class Game;
    static void Update(GameState& gameState);
  public:
    static int AddScene(GameState& gameState, SceneConfig config, int sceneId);
    static void SetScene(GameState& gameState, int sceneId);
  };
};
