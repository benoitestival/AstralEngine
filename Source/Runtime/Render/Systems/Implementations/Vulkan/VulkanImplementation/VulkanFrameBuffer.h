#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../../Utils/Array.h"

class FVulkanDevice;
class FVulkanSwapChain;
class FVulkanRenderPass;
class AVulkanRenderManager;

class FVulkanFrameBuffer {
public:
    FVulkanFrameBuffer();
    ~FVulkanFrameBuffer();
    
    VkResult Init(const TArray<VkImageView>& Attachements);
    void Clean();

    VkFramebuffer GetPrivateFrameBuffer();
private:
    AVulkanRenderManager* GetRenderManager() const;
    
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanDevice* GetVkDevice() const;
private:
    TArray<VkImageView> LinkedAttachement;
    VkFramebuffer FrameBuffer = VK_NULL_HANDLE;
    AVulkanRenderManager* RenderManager = nullptr;
};
