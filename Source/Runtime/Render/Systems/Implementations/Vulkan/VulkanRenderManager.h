#pragma once
#include "vulkan/vulkan.h"
#include "../../RenderManager.h"


class FVulkanSwapChain;
class FVulkanDevice;
class FVulkanSurface;



class AVulkanRenderManager : public ARenderManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanRenderManager, ARenderManager)
    AVulkanRenderManager() = default;
    
    void Init() override;
    void DeInit() override;

    VkInstance GetVkInstance();
    FVulkanDevice* GetVkDevice();
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanSurface* GetVkSurface() const;
private:
    //Instance Methods
    VkResult CreateInstance();

    //Vulkan Device Methods
    VkResult CreateVulkanDevice();
    void CleanVulkanDevice();
    
    //Vulkan Surface methods
    VkResult CreateVulkanSurface();
    void CleanVulkanSurface();

    //Vulkan SwapChain methods
    VkResult CreateVulkanSwapChain();
    void CleanVulkanSwapChain();
private:
    //Running Instance of Vulkan
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    //Physical GPU used by Vulkan
    
    FVulkanDevice* VulkanDevice = nullptr;
    FVulkanSurface* VulkanSurface = nullptr;
    FVulkanSwapChain* VulkanSwapChain = nullptr;
};
