#pragma once

#include "vk_api.hpp"

struct App
{
  VkAPI m_Instance;
  GLFWwindow* m_Window;

  App() = default;

  // Vulkan stuff
  void InitVulkan();

  void PickPhysicalDevice();

  void CleanUp();

  void EventLoop();

  // GLFW window stuff
  void CreateWindow();
};
