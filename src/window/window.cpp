#include "fate/window.h"
#include "fate/log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <memory>
#include <functional>

namespace Fate {
  void WindowManager::CreateWindow(WindowState &windowState) {
    LogMessage("Initializing window");
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      LogMessage( "SDL could not initialize!");
    }
    else {
      window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 200, 0);
      if( window == nullptr ) {
        LogMessage( "Window could not be created!");
      }
      else {
        LogMessage("Window ready!");
      }
    }
  }

  WindowManager::~WindowManager() {
    LogMessage("Shutting down window");
    if(window != nullptr) {
      SDL_DestroyWindow(window);
    }
    SDL_Quit();
    LogMessage("Window shutdown");
  }
};
