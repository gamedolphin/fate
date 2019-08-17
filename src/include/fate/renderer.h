#pragma once
#include <thread>
#include "entity.h"
#include "resource.h"
#include "shader.h"
#include "sprite.h"
#include "window.h"

namespace Fate {

struct RenderState {
  ShaderState shaderState;
  SpriteConstants spriteConstants;
  bool rendererInitialized = false;
  std::thread renderThread;
};

class Game;
struct GameState;

class Renderer {
  friend class Game;
  static void InitializeRenderer(WindowState& windowState,
                                 RenderState& renderState,
                                 EntityState& entityState);
  static void UpdateTransforms(GameState& gameState);
  static void SetupCameras(GameState& gameState);
  static void StartRenderer(GameState& gameState);
  static void Render(GameState& gameState);
  static void ShutdownRenderer(GameState& gameState);

 public:
  static entt::entity& MakeSprite(entt::entity& entity, GameState& gameState,
                                  std::string textureName);
};
};  // namespace Fate
