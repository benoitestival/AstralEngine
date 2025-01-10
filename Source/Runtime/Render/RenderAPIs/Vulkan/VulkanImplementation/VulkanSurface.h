#pragma once
#include "vulkan/vulkan.h"

class AGLFWWindow;
class AVulkanRenderer;

class FVulkanSurface {
public:
    FVulkanSurface();
    ~FVulkanSurface();
    
    VkResult Init();
    void Clean();

    VkSurfaceKHR GetPrivateSurface() const;
private:
    AVulkanRenderer* GetRenderManager() const;
    AGLFWWindow* GetWindow();
private:
    VkSurfaceKHR VkSurface = VK_NULL_HANDLE;
    AVulkanRenderer* RenderManager = nullptr;
};
    