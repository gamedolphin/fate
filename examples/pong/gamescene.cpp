#include "gamescene.h"
#include <fate/component_transform.h>
#include <fate/log.h>

using namespace Fate;

namespace Pong {

struct Player {};

struct Paddle {
  float maxSpeed;
  float height;
};

struct Collider {
  uint32_t height;
  uint32_t width;
};

struct Velocity {
  float x, y;
};

entt::entity MakePaddle(Fate::GameState& state, Fate::Scene& scene) {
  auto& registry = state.entityState.registry;
  auto paddle = scene.CreateEntity(state);
  Fate::Renderer::MakeSprite(paddle, state, "paddle");

  auto size = Fate::Resources::GetTextureSize(state, "paddle");

  auto& pInfo = registry.assign<Paddle>(paddle);
  pInfo.maxSpeed = 10;
  pInfo.height = (float)size.height;

  auto& collider = registry.assign<Collider>(paddle);
  collider.height = size.height;
  collider.width = size.width;

  registry.assign<Velocity>(paddle);
  return paddle;
}

void ProcessPaddles(GameState& state) {
  auto& registry = state.entityState.registry;
  auto& window = state.windowState;
  auto view = registry.view<Velocity, Transform, Paddle>();

  for (auto& entity : view) {
    auto& paddle = registry.get<Paddle>(entity);
    auto& velocity = registry.get<Velocity>(entity);
    auto& transform = registry.get<Transform>(entity);

    auto& position = transform.position;
    if (velocity.y < 0 &&
        position.y <= -window.height / 2 + paddle.height / 2) {
      velocity.y = 0;
    } else if (velocity.y > 0 &&
               position.y >= window.height / 2 - paddle.height / 2) {
      velocity.y = 0;
    }
  }
}

void ProcessInput(GameState& state, entt::entity& playerPaddle) {
  auto& paddle = state.entityState.registry.get<Paddle>(playerPaddle);
  auto& velocity = state.entityState.registry.get<Velocity>(playerPaddle);
  if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                Fate::KeyCode::W)) {
    velocity.y = paddle.maxSpeed;
  } else if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                       Fate::KeyCode::S)) {
    velocity.y = -paddle.maxSpeed;
  } else {
    velocity.y = 0;
  }
}

void ProcessBall(GameState& state, entt::entity ball) {
  auto& registry = state.entityState.registry;
  auto& ballCollider = registry.get<Collider>(ball);
  auto& ballTransform = registry.get<Transform>(ball);

  auto paddles = registry.view<Paddle, Transform, Collider>();

  for (auto& paddle : paddles) {
    auto& paddleTransform = registry.get<Transform>(paddle);
    auto& paddleCollider = registry.get<Collider>(paddle);
  }
}

void UpdatePositions(GameState& state) {
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

GameScene::GameScene(GameState& state) {
  sceneConfig.OnInitialize = [this](Fate::GameState& state,
                                    Fate::Scene& scene) {
    Fate::LogMessage("Initializing pong");

    Fate::Resources::LoadTexture(state, "textures/paddle.png", "paddle");
    Fate::Resources::LoadTexture(state, "textures/ball.png", "ball");

    auto paddleSize = Fate::Resources::GetTextureSize(state, "paddle");

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

    ball = scene.CreateEntity(state);
    Fate::Renderer::MakeSprite(ball, state, "ball");

    auto ballSize = Fate::Resources::GetTextureSize(state, "paddle");
    auto& collider = registry.assign<Collider>(ball);
    collider.height = ballSize.height;
    collider.width = ballSize.width;

    registry.assign<Velocity>(ball);
  };

  sceneConfig.OnUpdate = [this](Fate::GameState& state, Fate::Scene& scene) {
    ProcessInput(state, playerPaddle);
    ProcessPaddles(state);
    ProcessBall(state, ball);
    UpdatePositions(state);
  };
}

}  // namespace Pong
