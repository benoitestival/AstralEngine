#pragma once
#include <vulkan/vulkan_core.h>

class AVulkanRenderManager;

//Class Handling the swaping of the frame because Vulkan doesnt have a frame buffer 
class FVulkanSwapChain {
public:
    FVulkanSwapChain();
    ~FVulkanSwapChain();

    VkResult Init();
    void Clean();
private:
    AVulkanRenderManager* GetRenderManager() const;

private:
    AVulkanRenderManager* RenderManager = nullptr;

};
