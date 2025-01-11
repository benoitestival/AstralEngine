#include "VulkanLogger.h"

#include <iostream>

#include "../VulkanRenderer.h"
#include "../../../../Engine/Statics/GameplayStatics.h"

TArray<const char*> FVulkanLogger::ValidationLayers = {"VK_LAYER_KHRONOS_validation"};

FVulkanLogger::FVulkanLogger() {
}

FVulkanLogger::~FVulkanLogger() {
}

VkResult FVulkanLogger::Init() {
    VkResult Result = VK_SUCCESS;
    PFN_vkCreateDebugUtilsMessengerEXT CreateDubugMessengerFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(GetVKRenderer()->GetVkInstance(), "vkCreateDebugUtilsMessengerEXT");
    if (CreateDubugMessengerFunc != nullptr) {
        VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo = {};
        DebugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        DebugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        DebugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        DebugMessengerCreateInfo.pfnUserCallback = FVulkanLogger::DebugCallback2;
        
        Result = CreateDubugMessengerFunc(GetVKRenderer()->GetVkInstance(), &DebugMessengerCreateInfo, nullptr, &DebugMessenger);
    }
    else {
        Result = VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return Result;
}

void FVulkanLogger::Clean() {
    PFN_vkDestroyDebugUtilsMessengerEXT DestroyDubugMessengerFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(GetVKRenderer()->GetVkInstance(), "vkDestroyDebugUtilsMessengerEXT");
    if (DestroyDubugMessengerFunc != nullptr) {
        DestroyDubugMessengerFunc(GetVKRenderer()->GetVkInstance(), DebugMessenger, nullptr);
    }
}

VkBool32 FVulkanLogger::DebugCallback2(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}