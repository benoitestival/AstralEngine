#pragma once
#include <vulkan/vulkan_core.h>

#include "../VulkanObject.h"
#include "../../../../Utils/Array.h"
#include "../VulkanHelpers/VulkanRessource.h"

class FVulkanDevice;
class FVulkanSwapChain;
class FVulkanRenderPass;
class AVulkanRenderer;

class FVulkanFrameBuffer : public FVulkanObject, public TVulkanRessource<VkFramebuffer>{
public:
    FVulkanFrameBuffer();
    FVulkanFrameBuffer(const TArray<VkImageView>& Attachements);
    ~FVulkanFrameBuffer() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;
private:
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanDevice* GetVkDevice() const;
private:
    TArray<VkImageView> LinkedAttachement;
};
