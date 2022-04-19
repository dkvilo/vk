#include "vk_app.hpp"

void
App::InitVulkan()
{
  /**
   * @brief This is Instance of our abstraction top on the VK and not an
   * VkInstance In oreder to access the VkInscate you need to call the following
   * methid
   *
   */
  m_Instance = VkAPI();

#if defined(DEBUG)
  m_Instance.PrintExtensions();
#endif
}

void
App::CreateWindow()
{
  int status = glfwInit();
  Assert(status != GLFW_TRUE, "failed to init glfw");

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_Window = glfwCreateWindow(1080, 720, "Hello, World", nullptr, nullptr);
}

void
App::EventLoop()
{
  while (!glfwWindowShouldClose(m_Window)) {
    glfwPollEvents();
  }
}

void
App::CleanUp()
{
  VkInstance vkInstance = m_Instance.GetInstance();

  if (m_Instance.IsValidationEnabled()) {
    m_Instance.DestroyDebugUtilsMessengerEXT(
      vkInstance, m_Instance.GetDebugUtilsMessenger(), nullptr);
  }

  vkDestroyInstance(vkInstance, nullptr);

  glfwDestroyWindow(m_Window);

  glfwTerminate();
}
