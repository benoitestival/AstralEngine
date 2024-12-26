#pragma once
#include <vulkan/vulkan_core.h>

class FVulkanDevice;
class AVulkanRenderManager;

class FVulkanPipelineLayout {
public:
    FVulkanPipelineLayout();
    ~FVulkanPipelineLayout();
    
    VkResult Init();
    void Clean();

private:
    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;

private:
    AVulkanRenderManager* RenderManager = nullptr;
    VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
};
