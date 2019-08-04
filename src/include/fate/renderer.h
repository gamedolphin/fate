#pragma once
#include "window.h"
#include "shader.h"
#include "entity.h"
#include "sprite.h"
#include "resource.h"

namespace Fate {

  struct RenderState {
    ShaderState shaderState;
    SpriteConstants spriteConstants;
  };

  class Game;
  struct GameState;

  class Renderer {
    friend class Game;
    static void InitializeRenderer(WindowState& windowState, RenderState& renderState, EntityState& entityState);
    static void Render(WindowState& windowState, RenderState& renderState, EntityState &entityState);
    static void ShutdownRenderer(WindowState& windowState, RenderState& renderState);

  public:
    static entt::entity& MakeSprite(entt::entity &entity,
                           GameState& gameState,
                           std::string textureName);
  };
};
