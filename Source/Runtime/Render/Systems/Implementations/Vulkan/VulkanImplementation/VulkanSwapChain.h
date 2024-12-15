#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../../Utils/Array.h"

class FVulkanSurface;
class FVulkanDevice;
class AGLFWWindow;
class AVulkanRenderManager;


struct FSwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR Capabilities;
    TArray<VkSurfaceFormatKHR> Formats;
    TArray<VkPresentModeKHR> PresentModes;
};

//Class Handling the swaping of the frame because Vulkan doesnt have a frame buffer 
class FVulkanSwapChain {
public:
    FVulkanSwapChain();
    ~FVulkanSwapChain();

    VkResult Init();
    void Clean();

private:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const TArray<VkSurfaceFormatKHR>& AvailableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const TArray<VkPresentModeKHR>& AvailablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);
private:
    AGLFWWindow* GetActiveWindow() const;
    AVulkanRenderManager* GetRenderManager() const;

    FVulkanDevice* GetVkDevice() const;
    FVulkanSurface* GetVkSurface() const;
private:
    AVulkanRenderManager* RenderManager = nullptr;
    VkSwapchainKHR SwapChain = VK_NULL_HANDLE;

    TArray<VkImage> SwapChainImages;
    VkFormat SwapChainImageFormat;
    VkExtent2D SwapChainExtent;
};
