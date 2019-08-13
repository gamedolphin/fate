#include "gamescene.h"
#include <fate/component_transform.h>
#include <fate/log.h>

namespace Pong {

using namespace Fate;

struct Paddle {
  float maxSpeed;
  float height;
};

struct Collider {
  float x, y;
  float height;
  float width;

  static bool DoesIntersect(const Collider& c1, const Collider& c2) {
    auto l1x = c1.x - c1.width / 2;
    auto l1y = c1.y + c1.height / 2;
    auto r1x = c1.x + c1.width / 2;
    auto r1y = c1.y - c1.height / 2;

    auto l2x = c2.x - c2.width / 2;
    auto l2y = c2.y + c2.height / 2;
    auto r2x = c2.x + c2.width / 2;
    auto r2y = c2.y - c2.height / 2;

    if (l1x > r2x || l2x > r1x) return false;

    if (l1y < r2y || l2y < r1y) return false;

    return true;
  };
};

struct Velocity {
  float x, y;
};

struct Player {};
struct Ball {};

struct Active {};

struct Game_Playing {};
struct Game_Start {};

entt::entity MakePaddle(Fate::GameState& state, Fate::Scene& scene,
                        float posX) {
  auto& registry = state.entityState.registry;
  auto paddle = scene.CreateEntity(state);
  Fate::Renderer::MakeSprite(paddle, state, "paddle");

  auto size = Fate::Resources::GetTextureSize(state, "paddle");

  auto& pInfo = registry.assign<Paddle>(paddle);
  pInfo.maxSpeed = 10;
  pInfo.height = static_cast<float>(size.height);

  auto& playerTransform = registry.get<Transform>(paddle);
  SetTransformX(playerTransform, posX);

  auto& collider = registry.assign<Collider>(paddle);
  collider.x = posX;
  collider.y = 0;
  collider.height = size.height;
  collider.width = size.width;

  registry.assign<Velocity>(paddle);
  return paddle;
}

void ProcessPaddles(GameState& state) {
  auto& registry = state.entityState.registry;
  const auto& window = state.windowState;
  registry.view<Velocity, const Transform, const Paddle>().each(
      [window](Velocity& velocity, const Transform& transform,
               const Paddle& paddle) {
        auto& position = transform.position;
        if (velocity.y < 0 &&
            position.y <=
                -static_cast<float>(window.height) / 2 + paddle.height / 2) {
          velocity.y = 0;
        } else if (velocity.y > 0 &&
                   position.y >= static_cast<float>(window.height) / 2 -
                                     paddle.height / 2) {
          velocity.y = 0;
        }
      });
}

void ProcessInput(GameState& state) {
  auto& registry = state.entityState.registry;
  const auto& keyboardState = state.inputState.keyboardState;
  registry.view<Velocity, const Paddle, const Player>().each(
      [keyboardState](Velocity& velocity, const Paddle paddle,
                      const Player player) {
        if (Fate::Input::IsKeyPressed(keyboardState, Fate::KeyCode::W)) {
          velocity.y = paddle.maxSpeed;
        } else if (Fate::Input::IsKeyPressed(keyboardState, Fate::KeyCode::S)) {
          velocity.y = -paddle.maxSpeed;
        } else {
          velocity.y = 0;
        }
      });
}

void ProcessBall(GameState& state) {
  auto& registry = state.entityState.registry;
  registry.view<const Ball, const Collider, const Transform, Velocity>().each(
      [&registry](const auto& ball, const auto& active,
                  const auto& ballCollider, const auto& ballTransform,
                  auto& ballVelocity) {
        registry.view<const Paddle, const Transform, const Collider>().each(
            [ballCollider, &ballVelocity](const auto& paddle,
                                          const auto& paddleTransform,
                                          const auto& paddleCollider) {
              bool doesIntersect =
                  Collider::DoesIntersect(ballCollider, paddleCollider);

              if (doesIntersect == true) {
                ballVelocity.x *= -1;
              }
            });
      });
}

void UpdateColliders(GameState& state) {
  auto& registry = state.entityState.registry;
  registry.view<const Transform, Collider>().each(
      [](const Transform& transform, Collider& collider) {
        collider.x = transform.position.x;
        collider.y = transform.position.y;
      });
}

void UpdatePositions(GameState& state) {
  const float deltaTime = Time::GetDeltaTime(state);
  auto& registry = state.entityState.registry;
  registry.view<const Velocity, Transform>().each(
      [deltaTime](const Velocity& velocity, Transform& transform) {
        transform = SetTransformXY(
            transform, transform.position.x + velocity.x * deltaTime,
            transform.position.y + velocity.y);
      });
}

void ListenForSpace(GameState& state) {
  auto& registry = state.entityState.registry;

  registry.view<Game_Start>().each(
      [&state, &registry](entt::entity entity, const auto& start) {
        if (Fate::Input::IsKeyPressed(state.inputState.keyboardState,
                                      Fate::KeyCode::SPACE)) {
          state.entityState.registry.view<const Ball, Velocity>().each(
              [](const auto& ball, auto& velocity) { velocity.x = 1000; });

          registry.remove<Game_Start>(entity);
          registry.assign<Game_Playing>(entity);
        }
      });
}

GameScene::GameScene() {
  sceneConfig.OnInitialize = [this](Fate::GameState& state,
                                    Fate::Scene& scene) {
    Fate::LogMessage("Initializing pong");

    Fate::Resources::LoadTexture(state, "textures/paddle.png", "paddle");
    Fate::Resources::LoadTexture(state, "textures/ball.png", "ball");

    auto paddleSize = Fate::Resources::GetTextureSize(state, "paddle");

    auto& registry = state.entityState.registry;

    auto playerPosX = static_cast<float>(state.windowState.width) / 2 -
                      static_cast<float>(paddleSize.width) / 2;
    auto playerPaddle = MakePaddle(state, scene, playerPosX);
    registry.assign<Player>(playerPaddle);

    auto compPosX = -static_cast<float>(state.windowState.width) / 2 +
                    static_cast<float>(paddleSize.width) / 2;
    auto computerPaddle = MakePaddle(state, scene, compPosX);

    auto ball = scene.CreateEntity(state);
    Fate::Renderer::MakeSprite(ball, state, "ball");
    auto ballSize = Fate::Resources::GetTextureSize(state, "paddle");
    auto& collider = registry.assign<Collider>(ball);
    collider.x = 0;
    collider.y = 0;
    collider.height = ballSize.height;
    collider.width = ballSize.width;
    registry.assign<Velocity>(ball);
    registry.assign<Ball>(ball);

    auto gameConfig = scene.CreateEntity(state);
    registry.assign<Game_Start>(gameConfig);
  };

  sceneConfig.OnUpdate = [this](Fate::GameState& state, Fate::Scene& scene) {
    state.entityState.registry.view<Game_Playing>().each(
        [&state](const auto& config) {
          ProcessInput(state);
          ProcessPaddles(state);
          ProcessBall(state);
          UpdatePositions(state);
          UpdateColliders(state);
        });

    ListenForSpace(state);
  };
}

}  // namespace Pong
