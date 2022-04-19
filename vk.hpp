#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <map>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

#define Assert(check, message)                                                 \
  if ((check)) {                                                               \
    printf("Assertion failed: %s\n", message);                                 \
    exit(-1);                                                                  \
  }
