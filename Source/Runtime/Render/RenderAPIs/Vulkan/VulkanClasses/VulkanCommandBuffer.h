#pragma once
#include "VulkanFrameBuffer.h"

class FVulkanGraphicsPipeline;

class FVulkanCommandBuffer : public FVulkanObject, public TVulkanRessource<VkCommandBuffer>{
public:
    FVulkanCommandBuffer();
    ~FVulkanCommandBuffer() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;

    VkResult CreateCommandPool();
    void CleanCommandPool();

    VkResult RecordRenderPassCommand(int FRAME_INDEX);
private:

    FVulkanDevice* GetVkDevice() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
private:
    VkCommandPool CommandPool = VK_NULL_HANDLE;
    
};
