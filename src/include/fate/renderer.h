#pragma once
#include "window.h"
#include "shader.h"
#include "entity.h"

namespace Fate {

  struct RenderSize;

  struct RenderState {

  };

  class Game;

  class Renderer {
    friend class Game;

    Game *game;

    ShaderManager shaderManager;
    void InitializeRenderer(Game* game, WindowState& windowState, RenderState& renderState, EntityState& entityState);
    void Render(WindowState& windowState, RenderState& renderState, EntityState &entityState);
    void ShutdownRenderer(WindowState& windowState, RenderState& renderState);

  public:
    ~Renderer();
    entt::entity& MakeSprite(entt::entity& entity,
                             entt::registry& registry,
                             std::string textureName, RenderSize size);
  };
};
