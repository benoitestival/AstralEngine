#include "VulkanRenderManager.h"

#include <optional>
#include <GLFW/glfw3.h>

#include "VulkanImplementation/VulkanDevice.h"
#include "VulkanImplementation/VulkanSurface.h"


void AVulkanRenderManager::Init() {
    ARenderManager::Init();

    if (CreateInstance() == VK_SUCCESS) {
        CreateVulkanSurface();
        CreateVulkanDevice();
        CreateVulkanSwapChain();
    }
    else {
        //TODO throw an exception
    }
    
}

void AVulkanRenderManager::DeInit() {
    CleanVulkanSwapChain();
    CleanVulkanDevice();
    CleanVulkanSurface();
    vkDestroyInstance(VulkanInstance, nullptr);
    ARenderManager::DeInit();
}

VkInstance AVulkanRenderManager::GetVkInstance() {
    return VulkanInstance;
}

FVulkanDevice* AVulkanRenderManager::GetVkDevice() {
    return VulkanDevice;
}

FVulkanSwapChain* AVulkanRenderManager::GetVkSwapChain() const {
    return VulkanSwapChain;
}

FVulkanSurface* AVulkanRenderManager::GetVkSurface() const {
    return VulkanSurface;
}

VkResult AVulkanRenderManager::CreateInstance() {
    VkApplicationInfo VkAppInfo = {};
    VkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    VkAppInfo.pApplicationName = "Astral Engine";
    VkAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    VkAppInfo.pEngineName = "Astral Engine";
    VkAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    VkAppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo VkCreateInfo = {};
    VkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkCreateInfo.pApplicationInfo = &VkAppInfo;

    uint32_t GlfwExtensionCount;
    const char** GlfwExtensionsName;
    GlfwExtensionsName = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);
    
    VkCreateInfo.enabledExtensionCount = GlfwExtensionCount;
    VkCreateInfo.ppEnabledExtensionNames = GlfwExtensionsName;

    VkCreateInfo.enabledLayerCount = 0;

    return vkCreateInstance(&VkCreateInfo, nullptr, &VulkanInstance);
}

VkResult AVulkanRenderManager::CreateVulkanDevice() {
    VulkanDevice = new FVulkanDevice();
    return VulkanDevice->Init();
}

void AVulkanRenderManager::CleanVulkanDevice() {
    VulkanDevice->Clean();
    delete VulkanDevice;
    VulkanDevice = nullptr;
}

VkResult AVulkanRenderManager::CreateVulkanSurface() {
    VulkanSurface = new FVulkanSurface();
    return VulkanSurface->Init();
}

void AVulkanRenderManager::CleanVulkanSurface() {
    VulkanSurface->Clean();
    delete VulkanSurface;
    VulkanSurface = nullptr;
}

VkResult AVulkanRenderManager::CreateVulkanSwapChain() {
    VulkanSwapChain = new FVulkanSwapChain();
    return VulkanSwapChain->Init();
}

void AVulkanRenderManager::CleanVulkanSwapChain() {
    VulkanSwapChain->Clean();
    delete VulkanSwapChain;
    VulkanSwapChain = nullptr;
}
