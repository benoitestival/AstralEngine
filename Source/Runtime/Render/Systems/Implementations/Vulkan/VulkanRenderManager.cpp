#include "VulkanRenderManager.h"

#include <optional>
#include <GLFW/glfw3.h>

#include "VulkanImplementation/VulkanDevice.h"
#include "VulkanImplementation/VulkanGraphicsPipeline.h"
#include "VulkanImplementation/VulkanRenderPass.h"
#include "VulkanImplementation/VulkanSurface.h"


AVulkanRenderManager::AVulkanRenderManager() {
    
}

AVulkanRenderManager::~AVulkanRenderManager() {
}

void AVulkanRenderManager::Init() {
    ARenderManager::Init();

    if (CreateInstance() == VK_SUCCESS) {
        CreateVulkanSurface();
        CreateVulkanDevice();
        CreateVulkanSwapChain();
        CreateVulkanSwapChainImageViews();
        CreateVulkanRenderPass();
        CreateVulkanGraphicsPipeline();
        CreateVulkanFrameBuffers();
    }
    else {
        //TODO throw an exception
    }
    
}

void AVulkanRenderManager::DeInit() {
    CleanVulkanFrameBuffers();
    CleanVulkanGraphicsPipeline();
    CleanVulkanRenderPass();
    CleanVulkanSwapChainImageViews();
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

FVulkanRenderPass* AVulkanRenderManager::GetVkRenderPass() const {
    return VulkanRenderPass;
}

FVulkanGraphicsPipeline* AVulkanRenderManager::GetVkGraphicsPipeline() const {
    return VulkanGraphicsPipeline;
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

VkResult AVulkanRenderManager::CreateVulkanSwapChainImageViews() {
    return VulkanSwapChain->InitImageViews();
}

void AVulkanRenderManager::CleanVulkanSwapChainImageViews() {
    VulkanSwapChain->CleanImageViews();
}

VkResult AVulkanRenderManager::CreateVulkanFrameBuffers() {
    return VulkanSwapChain->InitFrameBuffers();
}

void AVulkanRenderManager::CleanVulkanFrameBuffers() {
    VulkanSwapChain->CleanFrameBuffers();
}

VkResult AVulkanRenderManager::CreateVulkanRenderPass() {
    VulkanRenderPass = new FVulkanRenderPass();
    return VulkanRenderPass->Init();
}

void AVulkanRenderManager::CleanVulkanRenderPass() {
    VulkanRenderPass->Clean();
    delete VulkanRenderPass;
    VulkanRenderPass = nullptr;
}

VkResult AVulkanRenderManager::CreateVulkanGraphicsPipeline() {
    VulkanGraphicsPipeline = new FVulkanGraphicsPipeline();
    return VulkanGraphicsPipeline->Init();
}

void AVulkanRenderManager::CleanVulkanGraphicsPipeline() {
    VulkanGraphicsPipeline->Clean();
    delete VulkanGraphicsPipeline;
    VulkanGraphicsPipeline = nullptr;
}
