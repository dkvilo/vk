#include "vk_device.hpp"

void
Vk_Device::CreateDevice()
{
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(m_Instance.GetInstance(), &deviceCount, nullptr);
  Assert(deviceCount > 0, "failed to find GPUs with Vulkan support");

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(
    m_Instance.GetInstance(), &deviceCount, devices.data());

  for (const auto& device : devices) {
    if (IsDeviceSuitable(device)) {
      m_PhysicalDevice = device;
      break;
    }
  }

  std::multimap<int, VkPhysicalDevice> candidates;

  for (const auto& device : devices) {
    int score = RateDeviceSuitability(device);
    candidates.insert(std::make_pair(score, device));
  }

  if (candidates.rbegin()->first > 0) {
    m_PhysicalDevice = candidates.rbegin()->second;
  } else {
    Assert(false, "failed to find a suitable GPU");
  }
}

bool
Vk_Device::IsDeviceSuitable(VkPhysicalDevice device)
{
  QueueFamilyIndices indices = FindQueueFamilies(device);
  return indices.IsComplete();
}

int
Vk_Device::RateDeviceSuitability(VkPhysicalDevice device)
{
  VkPhysicalDeviceProperties deviceProperties;
  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  int score = 0;
  if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 1000;
  }

  score += deviceProperties.limits.maxImageDimension2D;
  return score;
}

QueueFamilyIndices
Vk_Device::FindQueueFamilies(VkPhysicalDevice device)
{
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(
    device, &queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto& queueFamily : queueFamilies) {
    if (queueFamily.queueCount > 0 &&
        queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    if (indices.IsComplete()) {
      break;
    }

    i++;
  }

  return indices;
}
