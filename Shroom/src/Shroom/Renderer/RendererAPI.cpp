#include "RendererAPI.h"

#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Shroom {
    
    RendererAPI::API RendererAPI::_API = RendererAPI::API::Vulkan;

	Owned<RendererAPI> RendererAPI::Create() {
        switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:
            SCORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::Vulkan:
            return Own<VulkanRendererAPI>();
        }

        SCORE_ASSERT(false, "Unknown RendererAPI::API!");
        return nullptr;
	}

};

