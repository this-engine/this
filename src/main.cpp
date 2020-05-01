#include <stdio.h>
#include "core/core.hpp"
#include "core/sdl_window.hpp"

int main (int argc, char* args[]) 
{
  auto window = new TSDLWindow(TString("thisTest"), 640,480);
  window->run();
  delete window;
  return 0;
}