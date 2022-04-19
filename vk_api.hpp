#pragma once

#include "vk.hpp"

class VkAPI
{

public:
  VkAPI() { createVKInstace(); }

  VkInstance& GetInstance() { return m_Instance; }

  void PrintExtensions();

  void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks* pAllocator);

  bool IsValidationEnabled() const { return m_EnableValidationLayers; }

  VkDebugUtilsMessengerEXT& GetDebugUtilsMessenger()
  {
    return m_DebugMessenger;
  }

private:
  bool CheckValidationLayerSupport();

  std::vector<const char*> GetRequiredExtensions();

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

  void SetupDebugMessenger();

  VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);

  void PopulateDebugMessengerCreateInfo(
    VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
  std::vector<const char*> m_ValidationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

#ifdef NDEBUG
  bool m_EnableValidationLayers = false;
#else
  bool m_EnableValidationLayers = true;
#endif

private:
  VkInstance m_Instance;
  VkDebugUtilsMessengerEXT m_DebugMessenger;

private:
  void createVKInstace();
};
