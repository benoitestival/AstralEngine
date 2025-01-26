#pragma once
#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanRessource.h"

class FVulkanSurface;

class FVulkanPhysicalDevice : public FVulkanObject, public TVulkanRessource<VkPhysicalDevice>{
public:
    FVulkanPhysicalDevice();
    ~FVulkanPhysicalDevice() override;

    virtual VkResult Init() override;
    virtual void Clean() override;

    FQueueFamilyIndices GetSupportedQueueFamilies();
    FSwapChainSupportDetails QuerySwapChainSupportDetails();
private:
    FVulkanSurface* GetVkSurface() const;
private:  
    //Common Device Methods
    FQueueFamilyIndices GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device);
    FSwapChainSupportDetails QuerySwapChainSupportForDevice(VkPhysicalDevice Device);
    
    bool IsDeviceSuitable(VkPhysicalDevice Device);
    bool CheckDeviceSupportRequiredExtensions(VkPhysicalDevice Device);

    int GetDeviceSuitabilityScore(VkPhysicalDevice Device);
public:
    TArray<const char*> GetRequiredDeviceExtensions();
    TArray<std::string> GetRequiredDeviceExtensionsAsString();
};
