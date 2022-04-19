#include "vk_app.hpp"

int
main(int argc, char** argv)
{
  App app = App();

  app.InitVulkan();

  app.CreateWindow();

  app.EventLoop();

  app.CleanUp();

  return 0;
}
