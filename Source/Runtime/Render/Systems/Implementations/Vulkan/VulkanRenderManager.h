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
    bool CreateInstance();
    
    void SelectPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice Device);
    int GetDeviceSuitabilityScore(VkPhysicalDevice Device);
    FQueueFamilyIndices GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device);
private:
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
};
