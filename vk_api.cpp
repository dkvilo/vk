/**
 * @file vk_api.cpp
 * @author David Kviloria (you@domain.com)
 * @brief Vulkan API Setup and Debugging functions implementation
 */
#include "vk_api.hpp"

void
VkAPI::createVKInstace()
{
  Assert(m_EnableValidationLayers && !CheckValidationLayerSupport(),
         "Validation layers requested, but not available!");

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Vulkan, nice to meet you!";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "VKExample";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
  if (m_EnableValidationLayers) {
    createInfo.enabledLayerCount =
      static_cast<uint32_t>(m_ValidationLayers.size());
    createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

    PopulateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
  } else {
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
  Assert(result != VK_SUCCESS, "failed to create Vk instance");
}

std::vector<const char*>
VkAPI::GetRequiredExtensions()
{
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions,
                                      glfwExtensions + glfwExtensionCount);

  if (m_EnableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
  }

  return extensions;
}

bool
VkAPI::CheckValidationLayerSupport()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : m_ValidationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

void
VkAPI::PrintExtensions()
{
  uint32_t extensionCount = 0;
  VkResult extResult =
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  Assert(extResult != VK_SUCCESS, "failed to get extentions");

  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(
    nullptr, &extensionCount, extensions.data());

  printf("Available extensions: %d\n", extensionCount);
  for (const auto& extension : extensions) {
    printf("\t%s\n", extension.extensionName);
  }
}

VKAPI_ATTR VkBool32 VKAPI_CALL
VkAPI::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                     VkDebugUtilsMessageTypeFlagsEXT messageType,
                     const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                     void* pUserData)
{

  // Show only error messages
  if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    printf("Validation layer > %s\n", pCallbackData->pMessage);
  }

  return VK_FALSE;
}

VkResult
VkAPI::CreateDebugUtilsMessengerEXT(
  VkInstance instance,
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void
VkAPI::SetupDebugMessenger()
{
  if (!m_EnableValidationLayers) {
    return;
  }

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  PopulateDebugMessengerCreateInfo(createInfo);

  VkResult result = CreateDebugUtilsMessengerEXT(
    m_Instance, &createInfo, nullptr, &m_DebugMessenger);
  Assert(result != VK_SUCCESS, "failed to set up debug messenger");
}

void
VkAPI::DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks* pAllocator)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

void
VkAPI::PopulateDebugMessengerCreateInfo(
  VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = DebugCallback;
  createInfo.pUserData = nullptr;
}
