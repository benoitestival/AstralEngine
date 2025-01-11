#pragma once
#include <vulkan/vulkan_core.h>

#include "../VulkanObject.h"
#include "../VulkanHelpers/VulkanRessource.h"

class FVulkanDevice;
class AVulkanRenderer;

class FVulkanPipelineLayout : public FVulkanObject, public TVulkanRessource<VkPipelineLayout>{
public:
    FVulkanPipelineLayout();
    ~FVulkanPipelineLayout() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;

private:
    FVulkanDevice* GetVkDevice() const;
};
