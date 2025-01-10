#pragma once
#include <vulkan/vulkan_core.h>

class FVulkanSwapChain;
class FVulkanDevice;
class AVulkanRenderer;

class FVulkanRenderPass {
public:
    FVulkanRenderPass();
    ~FVulkanRenderPass();
    
    VkResult Init();
    void Clean();

    VkRenderPass GetPrivateRenderPass() const;
private:
    AVulkanRenderer* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain() const;
private:

    AVulkanRenderer* RenderManager = nullptr;
    
    VkRenderPass RenderPass = VK_NULL_HANDLE;
};
