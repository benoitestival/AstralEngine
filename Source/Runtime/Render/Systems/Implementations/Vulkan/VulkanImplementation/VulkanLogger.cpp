#include "VulkanLogger.h"

#include <iostream>

#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

TArray<const char*> FVulkanLogger::ValidationLayers = {"VK_LAYER_KHRONOS_validation"};

FVulkanLogger::FVulkanLogger() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanLogger::~FVulkanLogger() {
}

VkResult FVulkanLogger::Init() {
    VkResult Result = VK_SUCCESS;
    PFN_vkCreateDebugUtilsMessengerEXT CreateDubugMessengerFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(GetRenderManager()->GetVkInstance(), "vkCreateDebugUtilsMessengerEXT");
    if (CreateDubugMessengerFunc != nullptr) {
        VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo = {};
        DebugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        DebugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        DebugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        DebugMessengerCreateInfo.pfnUserCallback = FVulkanLogger::DebugCallback;
        
        Result = CreateDubugMessengerFunc(GetRenderManager()->GetVkInstance(), &DebugMessengerCreateInfo, nullptr, &DebugMessenger);
    }
    else {
        Result = VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return Result;
}

void FVulkanLogger::Clean() {
    PFN_vkDestroyDebugUtilsMessengerEXT DestroyDubugMessengerFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(GetRenderManager()->GetVkInstance(), "vkDestroyDebugUtilsMessengerEXT");
    if (DestroyDubugMessengerFunc != nullptr) {
        DestroyDubugMessengerFunc(GetRenderManager()->GetVkInstance(), DebugMessenger, nullptr);
    }
}

VkBool32 FVulkanLogger::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

AVulkanRenderManager* FVulkanLogger::GetRenderManager() const {
    return RenderManager;
}
