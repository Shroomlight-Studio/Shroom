#pragma once

#include "Platform/Vulkan/VulkanFactory.h"

namespace Shroom {

    struct VulkanFrame {
        vk::raii::CommandBuffer CommandBuffer;
        vk::raii::Semaphore ImageAvailableSemaphore;
        vk::raii::Semaphore RenderFinishedSemaphore;
        vk::raii::Fence Fence;
    };
    
} // namespace Shroom
