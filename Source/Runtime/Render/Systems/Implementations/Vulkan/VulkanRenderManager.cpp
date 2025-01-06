#include "VulkanRenderManager.h"

#include <iostream>
#include <optional>
#include <GLFW/glfw3.h>

#include "VulkanImplementation/VulkanCommandBuffer.h"
#include "VulkanImplementation/VulkanDevice.h"
#include "VulkanImplementation/VulkanGraphicsPipeline.h"
#include "VulkanImplementation/VulkanLogger.h"
#include "VulkanImplementation/VulkanRenderPass.h"
#include "VulkanImplementation/VulkanSurface.h"


AVulkanRenderManager::AVulkanRenderManager() {
    
}

AVulkanRenderManager::~AVulkanRenderManager() {
}

void AVulkanRenderManager::Init() {
    ARenderManager::Init();

    if (CreateInstance() == VK_SUCCESS) {
        CreateDebugMessenger();
        CreateVulkanSurface();
        CreateVulkanDevice();
        CreateVulkanSwapChain();
        CreateVulkanSwapChainImageViews();
        CreateVulkanRenderPass();
        CreateVulkanGraphicsPipeline();
        CreateVulkanFrameBuffers();
        CreateVulkanCommandBuffer();
        CreateSyncObjects();
    }
    
}

void AVulkanRenderManager::DeInit() {
    CleanSyncObjects();
    CleanVulkanCommandBuffer();
    CleanVulkanFrameBuffers();
    CleanVulkanGraphicsPipeline();
    CleanVulkanRenderPass();
    CleanVulkanSwapChainImageViews();
    CleanVulkanSwapChain();
    CleanVulkanDevice();
    CleanVulkanSurface();
    CleanDebugMessenger();
    vkDestroyInstance(VulkanInstance, nullptr);
    ARenderManager::DeInit();
}

void AVulkanRenderManager::Draw() {
    ARenderManager::Draw();

    //This function run and does not return until The fence are signaled
    // vkWaitForFences(GetVkDevice()->GetPrivateLogicalDevice(), 1, &InFlightFence, VK_TRUE, UINT64_MAX);
    //
    // //Reset to unsignaled
    // vkResetFences(GetVkDevice()->GetPrivateLogicalDevice(), 1, &InFlightFence);
    //
    // uint32_t ImageAcquiredIndex = INVALID_INDEX;
    // vkAcquireNextImageKHR(GetVkDevice()->GetPrivateLogicalDevice(), GetVkSwapChain()->GetPrivateSwapChain(), UINT64_MAX, ImageAvailableSemaphore, VK_NULL_HANDLE, &ImageAcquiredIndex);
    //
    // vkResetCommandBuffer(GetVkCommandBuffer()->GetPrivateCommandBuffer(), 0);
    //
    // auto Result = GetVkCommandBuffer()->RecordRenderPassCommand(ImageAcquiredIndex);
    //
    // VkSubmitInfo SubmitInfo = {};
    // SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    // SubmitInfo.waitSemaphoreCount = 1;
    //
    // TArray<VkSemaphore> WaitSemaphores = {ImageAvailableSemaphore};
    // TArray<VkSemaphore> SignalSemaphores = {RenderFinishedSemaphore};
    // TArray<VkPipelineStageFlags> WaitStages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    //
    // SubmitInfo.pWaitSemaphores = WaitSemaphores.Data();
    // SubmitInfo.pWaitDstStageMask = WaitStages.Data();
    //
    // SubmitInfo.commandBufferCount = 1;
    // VkCommandBuffer CommandBuffer = GetVkCommandBuffer()->GetPrivateCommandBuffer();
    // SubmitInfo.pCommandBuffers = &CommandBuffer;
    //
    // SubmitInfo.signalSemaphoreCount = 1;
    // SubmitInfo.pSignalSemaphores = SignalSemaphores.Data();
    //
    // vkQueueSubmit(GetVkDevice()->GetGraphicsQueue(), 1, &SubmitInfo, InFlightFence);
    //
    // VkPresentInfoKHR PresentInfo = {};
    // PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    //
    // PresentInfo.waitSemaphoreCount = 1;
    // PresentInfo.pWaitSemaphores = SignalSemaphores.Data();
    //
    // TArray<VkSwapchainKHR> SwapChains = {GetVkSwapChain()->GetPrivateSwapChain()};
    // PresentInfo.swapchainCount = 1;
    // PresentInfo.pSwapchains = SwapChains.Data();
    // PresentInfo.pImageIndices = &ImageAcquiredIndex;
    //
    // PresentInfo.pResults = nullptr;
    //
    // vkQueuePresentKHR(GetVkDevice()->GetPresentingQueue(), &PresentInfo);
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

FVulkanCommandBuffer* AVulkanRenderManager::GetVkCommandBuffer() const {
    return VulkanCommandBuffer;
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
    
    TArray<const char*> SupportedExtensions = GetRequiredExtensions();
    
    if (RunInDebug()) {
        SupportedExtensions.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    
    VkCreateInfo.enabledExtensionCount = SupportedExtensions.Lenght();
    VkCreateInfo.ppEnabledExtensionNames = SupportedExtensions.Data();

    if (RunInDebug()) {
        VkCreateInfo.enabledLayerCount = FVulkanLogger::ValidationLayers.Lenght();
        VkCreateInfo.ppEnabledLayerNames = FVulkanLogger::ValidationLayers.Data();
        
        VkDebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo = {};
        DebugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        DebugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        DebugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        DebugMessengerCreateInfo.pfnUserCallback = FVulkanLogger::DebugCallback;
        
        VkCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &DebugMessengerCreateInfo;
    }
    else {
        VkCreateInfo.enabledLayerCount = 0;
        VkCreateInfo.pNext = nullptr;
    }
    
    return vkCreateInstance(&VkCreateInfo, nullptr, &VulkanInstance);
}

VkResult AVulkanRenderManager::CreateDebugMessenger() {
    VkResult Result = VK_SUCCESS;
    if (RunInDebug()) {
        VulkanLogger = new FVulkanLogger();
        Result = VulkanLogger->Init();
    }
    return Result;
}

void AVulkanRenderManager::CleanDebugMessenger() {
    if (RunInDebug()) {
        VulkanLogger->Clean();
    }
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

VkResult AVulkanRenderManager::CreateVulkanCommandBuffer() {
    VulkanCommandBuffer = new FVulkanCommandBuffer();
    return VulkanCommandBuffer->Init();
}

void AVulkanRenderManager::CleanVulkanCommandBuffer() {
    VulkanCommandBuffer->Clean();
    delete VulkanCommandBuffer;
    VulkanCommandBuffer = nullptr;
}

VkResult AVulkanRenderManager::CreateSyncObjects() {
    VkSemaphoreCreateInfo SemaphoreCreateInfo = {};
    SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo FenceCreateInfo{};
    FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateSemaphore(GetVkDevice()->GetPrivateLogicalDevice(), &SemaphoreCreateInfo, nullptr, &ImageAvailableSemaphore);
    vkCreateSemaphore(GetVkDevice()->GetPrivateLogicalDevice(), &SemaphoreCreateInfo, nullptr, &RenderFinishedSemaphore);

    vkCreateFence(GetVkDevice()->GetPrivateLogicalDevice(), &FenceCreateInfo, nullptr, &InFlightFence);

    return VK_SUCCESS;
}

void AVulkanRenderManager::CleanSyncObjects() {
    vkDestroySemaphore(GetVkDevice()->GetPrivateLogicalDevice(), ImageAvailableSemaphore, nullptr);
    vkDestroySemaphore(GetVkDevice()->GetPrivateLogicalDevice(), RenderFinishedSemaphore, nullptr);
    vkDestroyFence(GetVkDevice()->GetPrivateLogicalDevice(), InFlightFence, nullptr);
}

TArray<const char*> AVulkanRenderManager::GetRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    return TArray<const char*>(Extensions);
}

bool AVulkanRenderManager::RunInDebug() const {
    bool IsDebug = false;
#if IS_VULKAN_DEBUG
    IsDebug = true;
#endif
    return IsDebug;
}

