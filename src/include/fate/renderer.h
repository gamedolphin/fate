#pragma once
#include "entity.h"
#include "resource.h"
#include "shader.h"
#include "sprite.h"
#include "window.h"

namespace Fate {

struct RenderState {
  ShaderState shaderState;
  SpriteConstants spriteConstants;
};

class Game;
struct GameState;

class Renderer {
  friend class Game;
  static void InitializeRenderer(WindowState& windowState,
                                 RenderState& renderState,
                                 EntityState& entityState);
  static void UpdateTransforms(GameState& gameState);
  static void Render(WindowState& windowState, RenderState& renderState,
                     EntityState& entityState);
  static void ShutdownRenderer(WindowState& windowState,
                               RenderState& renderState);

 public:
  static entt::entity& MakeSprite(entt::entity& entity, GameState& gameState,
                                  std::string textureName);
};
};  // namespace Fate
