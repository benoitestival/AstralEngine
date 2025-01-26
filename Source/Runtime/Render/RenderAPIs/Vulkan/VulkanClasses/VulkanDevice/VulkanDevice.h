#pragma once

#include <set>
#include <string>

#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanRessource.h"
#include "vulkan/vulkan.h"

class FVulkanPhysicalDevice;
class FVulkanSurface;
class AVulkanRenderer;



class FVulkanDevice : public FVulkanObject, public TVulkanRessource<VkDevice>{
public:
    FVulkanDevice();
    ~FVulkanDevice() override;

    VkResult Init() override;
    void Clean() override;

    VkQueue GetGraphicsQueue() const;
    VkQueue GetPresentingQueue() const;

    FVulkanPhysicalDevice* GetVkPhysicalDevice() const;
private:
    //Physical Device Methods
    VkResult SelectPhysicalDevice();
    void CleanPhysicalDevice();
private:
    FVulkanPhysicalDevice* PhysicalDevice = nullptr;
    
    //QueueFamilies
    VkQueue GraphicsQueue = VK_NULL_HANDLE;
    VkQueue PresentingQueue = VK_NULL_HANDLE;
    
};
