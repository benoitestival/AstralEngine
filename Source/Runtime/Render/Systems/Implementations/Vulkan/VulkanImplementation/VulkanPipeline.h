#pragma once
#include <vulkan/vulkan_core.h>

class AVulkanRenderManager;
class FVulkanDevice;

class FVulkanPipeline {
public:
    FVulkanPipeline();
    ~FVulkanPipeline();
    
    VkResult Init();
    void Clean();
private:
    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;

private:
    AVulkanRenderManager* RenderManager = nullptr;
};
