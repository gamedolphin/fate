#include "gamescene.h"
#include <fate/component_transform.h>
#include <fate/log.h>

using namespace Fate;

namespace Pong {

struct Player {};

entt::entity MakePaddle(Fate::GameState& state, Fate::Scene& scene) {
  auto& registry = state.entityState.registry;
  auto paddle = scene.CreateEntity(state);
  Fate::Renderer::MakeSprite(paddle, state, "paddle");
  registry.assign<Paddle>(paddle);
  registry.assign<Velocity>(paddle);
  return paddle;
}

GameScene::GameScene(GameState& state) {
  sceneConfig.OnInitialize = [&](Fate::GameState& state, Fate::Scene& scene) {
    Fate::LogMessage("Initializing pong");

    Fate::Resources::LoadTexture(state, "textures/paddle.png", "paddle");
    Fate::Resources::LoadTexture(state, "textures/ball.png", "ball");

    paddleSize = Fate::Resources::GetTextureSize(state, "paddle");

    auto& registry = state.entityState.registry;

    playerPaddle = MakePaddle(state, scene);
    registry.assign<Player>(playerPaddle);
    auto& playerTransform = registry.get<Transform>(playerPaddle);
    SetTransformX(playerTransform,
                  state.windowState.width / 2 - (float)paddleSize.width / 2);

    auto computerPaddle = MakePaddle(state, scene);
    auto& computerTransform = registry.get<Transform>(computerPaddle);
    SetTransformX(computerTransform,
                  -state.windowState.width / 2 + (float)paddleSize.width / 2);

    auto ball = scene.CreateEntity(state);
    Fate::Renderer::MakeSprite(ball, state, "ball");
    registry.assign<Velocity>(ball);
  };

  sceneConfig.OnUpdate = [this](Fate::GameState& state, Fate::Scene& scene) {
    ProcessInput(state, playerPaddle);
    ProcessPaddles(state);
    UpdatePositions(state);
  };
}

void GameScene::ProcessPaddles(GameState& state) {
  auto& registry = state.entityState.registry;
  auto& window = state.windowState;
  auto view = registry.view<Velocity, Transform, Paddle>();

  for (auto& entity : view) {
    auto& velocity = registry.get<Velocity>(entity);
    auto& transform = registry.get<Transform>(entity);

    auto& position = transform.position;
    if (velocity.y < 0 &&
        position.y <= -window.height / 2 + (float)paddleSize.height / 2) {
      velocity.y = 0;
    } else if (velocity.y > 0 &&
               position.y >= window.height / 2 - (float)paddleSize.height / 2) {
      velocity.y = 0;
    }
  }
}

void GameScene::ProcessInput(GameState& state, entt::entity& playerPaddle) {
  auto& velocity = state.entityState.registry.get<Velocity>(playerPaddle);
  if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                Fate::KeyCode::W)) {
    velocity.y = paddleSpeed;
  } else if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                       Fate::KeyCode::S)) {
    velocity.y = -paddleSpeed;
  } else {
    velocity.y = 0;
  }
}

void GameScene::UpdatePositions(GameState& state) {
  float deltaTime = Time::GetDeltaTime(state);
  auto& registry = state.entityState.registry;
  auto view = registry.view<Velocity, Transform>();

  for (auto& entity : view) {
    auto& transform = registry.get<Transform>(entity);
    auto& velocity = registry.get<Velocity>(entity);

    transform =
        SetTransformXY(transform, transform.position.x + velocity.x * deltaTime,
                       transform.position.y + velocity.y);
  }
}

}  // namespace Pong
