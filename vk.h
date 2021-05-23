/**
 * 
 * @author David Kviloria
 * @version N/A
 * @date N/A
 * description exploring vk api
 * 
 */
#ifndef __VK_H__
#define __VK_H__

#include <stdio.h>
#include <stdlib.h>

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define Assert(check, message)                 \
  if ((check))                                 \
  {                                            \
    printf("Assertion failed: %s\n", message); \
    exit(-1);                                  \
  }

class VkAPI
{

public:
  VkAPI()
  {
    createVKInstace();
  }

  VkInstance GetInstance() const
  {
    return m_Instance;
  }

private:
  VkInstance m_Instance;

private:
  void createVKInstace();
};

struct Sandbox
{
  VkAPI m_Instance;
  bool m_IsRunning = false;

  Sandbox() = default;

  // Vulkan stuff
  void InitVulkan();
  void CleanUp();
  void EventLoop();

  // GLFW window stuff
  void CreateWindow();
};

// ################# IMPLEMENTATION ######################

void VkAPI::createVKInstace()
{
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Vulkan, nice to meet you!";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "VKExample";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  createInfo.pApplicationInfo = &appInfo;

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
  Assert((result != VK_SUCCESS), "failed to create Vk instance");
}

void Sandbox::InitVulkan()
{
  /**
   * 
   * This is Instance of our abstraction top on the VK and not an VkInstance
   * In oreder to access the VkInscate you need to call the following methid
   *
   */
  m_Instance = VkAPI();
}

void Sandbox::CreateWindow() {}
void Sandbox::EventLoop() {}
void Sandbox::CleanUp() {}

int main()
{

  Sandbox app = Sandbox();
  app.InitVulkan();
  app.CreateWindow();
  app.EventLoop();
  app.CleanUp();

  return 0;
}

#endif // __VK_H__