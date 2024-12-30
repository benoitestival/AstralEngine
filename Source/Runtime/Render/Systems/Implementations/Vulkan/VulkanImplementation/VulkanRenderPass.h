#pragma once
#include <vulkan/vulkan_core.h>

class FVulkanSwapChain;
class FVulkanDevice;
class AVulkanRenderManager;

class FVulkanRenderPass {
public:
    FVulkanRenderPass();
    ~FVulkanRenderPass();
    
    VkResult Init();
    void Clean();

    VkRenderPass GetPrivateRenderPass() const;
private:
    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain() const;
private:

    AVulkanRenderManager* RenderManager = nullptr;
    
    VkRenderPass RenderPass = VK_NULL_HANDLE;
};
