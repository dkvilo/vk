#pragma once

#include "vk.hpp"
#include "vk_api.hpp"

struct QueueFamilyIndices
{
  int graphicsFamily = -1;
  int presentFamily = -1;

  bool IsComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
};

class Vk_Device
{
public:
  void CreateDevice();
  void DestroyDevice();

  void PickDevice();

  VkDevice& GetDevice() { return m_Device; }
  VkPhysicalDevice& GetPhysicalDevice() { return m_PhysicalDevice; }
  VkQueue& GetGraphicsQueue() { return m_GraphicsQueue; }

private:
  bool IsDeviceSuitable(VkPhysicalDevice device);
  int RateDeviceSuitability(VkPhysicalDevice device);
  QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

private:
  VkAPI m_Instance;
  VkDevice m_Device;
  VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
  VkQueue m_GraphicsQueue;
};
