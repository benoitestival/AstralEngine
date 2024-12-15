#pragma once

#include <string>

#include "VulkanSwapChain.h"
#include "../../../../../Utils/Array.h"
#include "vulkan/vulkan.h"

class FVulkanSurface;
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
    TArray<uint32_t> ToUnsignedArray() {
        return {(uint32_t)GraphicsFamilyIndice, (uint32_t)PresentingFamilyIndice};
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

    //Logical Device Methods
    VkResult CreateLogicalDevice();

private:
    //Physical Device Methods
    bool IsDeviceSuitable(VkPhysicalDevice Device);
    int GetDeviceSuitabilityScore(VkPhysicalDevice Device);
    bool CheckDeviceSupportRequiredExtensions(VkPhysicalDevice Device);
    TArray<const char*> GetRequiredDeviceExtensions();
    TArray<std::string> GetRequiredDeviceExtensionsAsString();
public:
    FSwapChainSupportDetails QuerySwapChainSupportDetails();
private:
    FSwapChainSupportDetails QuerySwapChainSupportForDevice(VkPhysicalDevice Device);

public:
    FQueueFamilyIndices GetSupportedQueueFamilies();
private:  
    //Common Device Methods
    FQueueFamilyIndices GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device);

    ///////////////////////////////////////////////////////////
    AVulkanRenderManager* GetRenderManager() const;
    FVulkanSurface* GetVkSurface() const;
private:
    AVulkanRenderManager* RenderManager = nullptr;

    //Physical GPU used by Vulkan
    VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
    //Logical device used by Vulkan
    VkDevice LogicalDevice = VK_NULL_HANDLE;

    //QueueFamilies
    VkQueue GraphicsQueue = VK_NULL_HANDLE;
    VkQueue PresentingQueue = VK_NULL_HANDLE;
    
};
