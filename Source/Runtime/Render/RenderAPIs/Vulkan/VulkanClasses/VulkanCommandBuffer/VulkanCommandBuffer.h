#pragma once
#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanRessource.h"

class FVulkanSwapChain;
class FVulkanRenderPass;
class FVulkanDevice;
class FVulkanVertexBuffer;
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
    VkCommandPool& GetCommandPool();
private:

    FVulkanDevice* GetVkDevice() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
    FVulkanVertexBuffer* GetVkVertexBuffer() const;
private:
    VkCommandPool CommandPool = VK_NULL_HANDLE;
    
};
