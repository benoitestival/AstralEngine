#pragma once
#include "vulkan/vulkan.h"

class AGLFWWindow;
class AVulkanRenderManager;

class FVulkanSurface {
public:
    FVulkanSurface();
    ~FVulkanSurface();
    
    VkResult Init();
    void Clean();

    VkSurfaceKHR GetPrivateSurface() const;
private:
    AVulkanRenderManager* GetRenderManager() const;
    AGLFWWindow* GetWindow();
private:
    VkSurfaceKHR VkSurface = VK_NULL_HANDLE;
    AVulkanRenderManager* RenderManager = nullptr;
};
    