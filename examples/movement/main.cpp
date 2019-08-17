#include <fate/component_transform.h>
#include <fate/core.h>
#include <fate/gamestate.h>
#include <fate/input.h>
#include <fate/log.h>
#include <fate/time.h>
#include <iostream>

struct FateLogo {};

int main(int argc, char** argv) {
  Fate::GameState gameState;
  gameState.windowState = {
      .windowTitle = "Movement Test", .width = 800, .height = 600};

  Fate::SceneConfig sceneConfig;
  sceneConfig.OnInitialize = [](Fate::GameState& state, Fate::Scene& scene) {
    Fate::LogMessage("Initializing game");
    Fate::Resources::LoadTexture(state, "textures/FATE.png", "Fate");
    auto entity = scene.CreateEntity(state);
    Fate::Renderer::MakeSprite(entity, state, "Fate");
    state.entityState.registry.assign<FateLogo>(entity);
  };

  float maxSpeed = 100;
  float speedX = 0;
  float speedY = 0;
  sceneConfig.OnUpdate = [&](Fate::GameState& state, Fate::Scene& scene) {
    float multiplier = Fate::Time::GetDeltaTime(state);
    auto& registry = state.entityState.registry;
    auto view = registry.view<FateLogo, Fate::Transform>();

    for (auto& entity : view) {
      auto& transform = registry.get<Fate::Transform>(entity);

      speedX = 0;
      speedY = 0;

      if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                    Fate::KeyCode::W)) {
        speedY = maxSpeed;
      } else if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                           Fate::KeyCode::S)) {
        speedY = -maxSpeed;
      }

      if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                    Fate::KeyCode::A)) {
        speedX = -maxSpeed;
      } else if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                           Fate::KeyCode::D)) {
        speedX = maxSpeed;
      }

      transform = Fate::SetTransformXY(
          transform, transform.position.x + speedX * multiplier,
          transform.position.y + speedY * multiplier);
    }
  };

  auto sceneId = Fate::Scenes::AddScene(gameState, sceneConfig, 0);
  Fate::Scenes::SetScene(gameState, sceneId);

  Fate::Game::Run(gameState);

  return 0;
}
