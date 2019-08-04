#include <iostream>
#include "fate/core.h"
#include "fate/log.h"
#include "fate/gamestate.h"
#include "fate/component_transform.h"

struct FateLogo {};

int main(int argc, char** argv) {

  Fate::GameState gameState;
  gameState.windowState = {
                           .windowTitle = "Sprite Test",
                           .width = 800,
                           .height = 600
  };

  Fate::Game::Initialize(gameState);
  Fate::Resources::LoadTexture(gameState,"textures/FATE.png", "Fate");

  Fate::SceneConfig sceneConfig;
  sceneConfig.OnInitialize = [](Fate::GameState& state, Fate::Scene& scene) {
                               Fate::LogMessage("Initializing game");

                               auto entity = scene.CreateEntity(state);
                               Fate::Renderer::MakeSprite(entity, state, "Fate");
                               state.entityState.registry.assign<FateLogo>(entity);
                             };

  float speedConstX = 1;
  float speedConstY = 0.7f;
  float maxX = 1;
  float maxY = 1;
  float multiplier = 0.01f;
  float speedX = speedConstX;
  float speedY = speedConstY;
  sceneConfig.OnUpdate = [&](Fate::GameState& state, Fate::Scene& scene) {

                           auto &registry = state.entityState.registry;
                           auto view = registry.view<FateLogo,Fate::Transform>();

                           for(auto &entity : view) {
                             auto &transform = registry.get<Fate::Transform>(entity);
                             if(transform.position.x > maxX) {
                               speedX = -speedConstX;
                             }
                             else if(transform.position.x < -maxX){
                               speedX = speedConstX;
                             }

                             if(transform.position.y > maxY) {
                               speedY = -speedConstY;
                             }
                             else if(transform.position.y < -maxY) {
                               speedY = speedConstX;
                             }

                             transform = Fate::SetTransformXY(transform, transform.position.x + speedX*multiplier, transform.position.y + speedY * multiplier);
                           }
                         };


  int sceneId = Fate::Scenes::AddScene(gameState, sceneConfig, 0);

  Fate::Scenes::SetScene(gameState, sceneId);

  Fate::Game::Run(gameState);

  return 0;
}
