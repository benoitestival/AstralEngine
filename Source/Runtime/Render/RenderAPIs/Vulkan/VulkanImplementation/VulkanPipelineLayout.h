#pragma once
#include <vulkan/vulkan_core.h>

class FVulkanDevice;
class AVulkanRenderer;

class FVulkanPipelineLayout {
public:
    FVulkanPipelineLayout();
    ~FVulkanPipelineLayout();
    
    VkResult Init();
    void Clean();

    VkPipelineLayout GetPrivatePipelineLayout() const;
private:
    AVulkanRenderer* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;

private:
    AVulkanRenderer* RenderManager = nullptr;
    VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
};
