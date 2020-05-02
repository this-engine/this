#include <stdio.h>
#include "core/core.hpp"
#include "core/glfw_window.hpp"

int main (int argc, char* args[]) 
{
  auto window = new TGLFWWindow(TString("this-demo-window"), 640,480);
  window->run();
  delete window;
  return 0;
}
