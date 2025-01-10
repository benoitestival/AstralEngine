#pragma once
#include "VulkanFrameBuffer.h"

class FVulkanGraphicsPipeline;

class FVulkanCommandBuffer {
public:
    FVulkanCommandBuffer();
    ~FVulkanCommandBuffer();
    
    VkResult Init();
    void Clean();

    VkResult CreateCommandPool();
    void CleanCommandPool();

    VkResult RecordRenderPassCommand(int FRAME_INDEX);
    VkCommandBuffer GetPrivateCommandBuffer() const;
private:
    AVulkanRenderer* GetRenderManager() const;

    FVulkanDevice* GetVkDevice() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
private:
    VkCommandPool CommandPool = VK_NULL_HANDLE;
    VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
    AVulkanRenderer* RenderManager = nullptr;
    
};
