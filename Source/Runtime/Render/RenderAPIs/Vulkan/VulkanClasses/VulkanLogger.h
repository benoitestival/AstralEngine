#pragma once
#include <vulkan/vulkan_core.h>

#include "../VulkanObject.h"
#include "../../../../Utils/Array.h"


class AVulkanRenderer;

class FVulkanLogger : public FVulkanObject{
public:

    FVulkanLogger();
    ~FVulkanLogger() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;
    
    //Static methdds who is used as a callback
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback2(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
public:
    static TArray<const char*> ValidationLayers;
private:
    VkDebugUtilsMessengerEXT DebugMessenger = VK_NULL_HANDLE;

};
