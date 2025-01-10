#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../Utils/Array.h"


class AVulkanRenderer;

class FVulkanLogger {
public:

    FVulkanLogger();
    ~FVulkanLogger();
    
    VkResult Init();
    void Clean();
    
    //Static methdds who is used as a callback
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback2(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
private:
    AVulkanRenderer* GetRenderManager() const;
public:
    static TArray<const char*> ValidationLayers;
private:
    VkDebugUtilsMessengerEXT DebugMessenger = VK_NULL_HANDLE;
    AVulkanRenderer* RenderManager = nullptr;

};
