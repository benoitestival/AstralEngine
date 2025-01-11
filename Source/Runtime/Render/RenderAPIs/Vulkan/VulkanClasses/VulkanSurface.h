#pragma once
#include "../VulkanObject.h"
#include "../VulkanHelpers/VulkanRessource.h"
#include "vulkan/vulkan.h"

class AGLFWWindow;
class AVulkanRenderer;

class FVulkanSurface : public FVulkanObject, public TVulkanRessource<VkSurfaceKHR>{
public:
    FVulkanSurface();
    ~FVulkanSurface() override;

    virtual VkResult Init() override;
    virtual void Clean() override;

    //VkSurfaceKHR GetPrivateSurface() const;
private:
    //AVulkanRenderer* GetRenderManager() const;
    AGLFWWindow* GetWindow();
private:
    // VkSurfaceKHR VkSurface = VK_NULL_HANDLE;
    // AVulkanRenderer* RenderManager = nullptr;
};
    