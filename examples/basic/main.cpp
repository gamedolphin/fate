#include <iostream>
#include "fate/core.h"
#include "fate/log.h"
#include "fate/gamestate.h"

using namespace Fate;

int main(int argc, char** argv) {

  GameState gameState;
  Game game;

  game.Run(gameState);
  return 0;
}
