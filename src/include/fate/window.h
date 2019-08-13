#pragma once
#include <string>

struct SDL_Window;

namespace Fate {

class Game;

struct WindowState {
  SDL_Window* windowHandle;
  int width, height;
  std::string windowTitle;
};

class Window {
  friend class Game;
  static void CreateWindow(WindowState& state);
  static void ShutdownWindow(WindowState& state);
};

void* GetDisplayType(WindowState& windowState);
void* GetWindowHandle(WindowState& windowState);
}  // namespace Fate
