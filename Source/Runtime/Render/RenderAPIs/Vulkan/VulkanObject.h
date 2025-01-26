#pragma once
#include <vulkan/vulkan_core.h>
#include "VulkanHelpers/VulkanTypes.h"

class AVulkanRenderer;

class FVulkanObject {
public:
    FVulkanObject();
    virtual ~FVulkanObject() = default;
    
    virtual VkResult Init();
    virtual void Clean();
protected:
    AVulkanRenderer* GetVKRenderer() const;
private:
    AVulkanRenderer* Renderer;

};
