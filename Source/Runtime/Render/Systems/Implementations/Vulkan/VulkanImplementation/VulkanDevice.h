#pragma once

#include "../../../../../Utils/Array.h"
#include "vulkan/vulkan.h"

class AVulkanRenderManager;

#define INVALID_FAMILY_INDICE -1

struct FQueueFamilyIndices {
    int GraphicsFamilyIndice = -1;
    int PresentingFamilyIndice = -1;

    bool IsValid() const {
        return GraphicsFamilyIndice != INVALID_FAMILY_INDICE && PresentingFamilyIndice != INVALID_FAMILY_INDICE;
    }

    TArray<int> ToArray() {
        return {GraphicsFamilyIndice, PresentingFamilyIndice};
    }
};


class FVulkanDevice {
public:
    FVulkanDevice();
    ~FVulkanDevice();

    VkResult Init();
    void Clean();

    VkPhysicalDevice GetPrivatePhysicalDevice() const;
    VkDevice GetPrivateLogicalDevice() const;
private:
    //Physical Device Methods
    VkResult SelectPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice Device);
    int GetDeviceSuitabilityScore(VkPhysicalDevice Device);

    //Logical Device Methods
    VkResult CreateLogicalDevice();

    //Common Device Methods
    FQueueFamilyIndices GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device);

    ///////////////////////////////////////////////////////////
    AVulkanRenderManager* GetRenderManager() const;
private:
    AVulkanRenderManager* RenderManager = nullptr;

    //Physical GPU used by Vulkan
    VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
    //Logical device used by Vulkan
    VkDevice LogicalDevice = VK_NULL_HANDLE;
    
    VkQueue GraphicsQueue = VK_NULL_HANDLE;
    VkQueue PresentingQueue = VK_NULL_HANDLE;
    
};
