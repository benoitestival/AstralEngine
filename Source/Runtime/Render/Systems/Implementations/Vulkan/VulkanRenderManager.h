#pragma once
#include "vulkan/vulkan.h"
#include "../../RenderManager.h"

#define INVALID_FAMILY_INDICE -1

struct FQueueFamilyIndices {
    int GraphicsFamilyIndice = -1;

    bool IsValid() const {
        return GraphicsFamilyIndice != INVALID_FAMILY_INDICE;
    }
};


class AVulkanRenderManager : public ARenderManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanRenderManager, ARenderManager)
    AVulkanRenderManager() = default;
    
    void Init() override;
    void DeInit() override;
private:
    //Instance Methods
    VkResult CreateInstance();

    //Physical Device Methods
    VkResult SelectPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice Device);
    int GetDeviceSuitabilityScore(VkPhysicalDevice Device);

    //Logical Device Methods
    VkResult CreateLogicalDevice();

    //Common Device Methods
    FQueueFamilyIndices GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device);
private:
    //Running Instance of Vulkan
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    //Physical GPU used by Vulkan
    VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
    //Logical device used by Vulkan
    VkDevice LogicalDevice = VK_NULL_HANDLE;
    
    VkQueue GraphicsQueue = VK_NULL_HANDLE;
};
