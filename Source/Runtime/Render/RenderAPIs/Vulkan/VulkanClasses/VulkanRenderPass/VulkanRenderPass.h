#pragma once
#include <vulkan/vulkan_core.h>

#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanRessource.h"


class FVulkanSwapChain;
class FVulkanDevice;
class AVulkanRenderer;

class FVulkanRenderPass : public FVulkanObject, public TVulkanRessource<VkRenderPass>{
public:
    FVulkanRenderPass();
    ~FVulkanRenderPass() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;

private:
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain() const;
};
