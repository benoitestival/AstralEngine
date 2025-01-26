#pragma once
#include <vulkan/vulkan_core.h>

#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanRessource.h"


class FVulkanFrameBuffer;
class FVulkanSurface;
class FVulkanDevice;
class AGLFWWindow;
class AVulkanRenderer;


//Class Handling the swaping of the frame because Vulkan doesnt have a frame buffer 
class FVulkanSwapChain : public FVulkanObject, public TVulkanRessource<VkSwapchainKHR>{
public:
    FVulkanSwapChain();
    ~FVulkanSwapChain() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;

    VkResult InitImageViews();
    void CleanImageViews();

    VkResult InitFrameBuffers();
    void CleanFrameBuffers();

    VkFormat GetFormat() const;
    VkExtent2D GetExtent() const;
    VkViewport GetViewport();
    VkRect2D GetScissor();
    FVulkanFrameBuffer* GetFrameBuffer(int FRAME_BUFFER_INDEX) const;
private:
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const TArray<VkSurfaceFormatKHR>& AvailableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const TArray<VkPresentModeKHR>& AvailablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);
private:
    AGLFWWindow* GetActiveWindow() const;

    FVulkanDevice* GetVkDevice() const;
    FVulkanSurface* GetVkSurface() const;
private:
    TArray<VkImage> SwapChainImages;
    TArray<VkImageView> SwapChainImageViews;
    
    TArray<FVulkanFrameBuffer*> SwapChainFrameBuffers;
    
    VkFormat SwapChainImageFormat;
    VkExtent2D SwapChainExtent;

    VkViewport Viewport;
    VkRect2D Scissor;
};
