#include "VulkanRenderer.h"

#include <iostream>
#include <optional>
#include <GLFW/glfw3.h>

#include "VulkanImplementation/VulkanCommandBuffer.h"
#include "VulkanImplementation/VulkanDevice.h"
#include "VulkanImplementation/VulkanGraphicsPipeline.h"
#include "VulkanImplementation/VulkanLogger.h"
#include "VulkanImplementation/VulkanRenderPass.h"
#include "VulkanImplementation/VulkanSurface.h"


AVulkanRenderer::AVulkanRenderer() {
    
}

AVulkanRenderer::~AVulkanRenderer() {
}

void AVulkanRenderer::Init() {
    ARenderer::Init();

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

void AVulkanRenderer::DeInit() {
    vkDeviceWaitIdle(GetVkDevice()->GetPrivateLogicalDevice());
    
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
    ARenderer::DeInit();
}

void AVulkanRenderer::Draw() {
    ARenderer::Draw();
    
    //This function run and does not return until The fence are signaled
    vkWaitForFences(GetVkDevice()->GetPrivateLogicalDevice(), 1, &InFlightFence, VK_TRUE, UINT64_MAX);
    
    //Reset to unsignaled
    vkResetFences(GetVkDevice()->GetPrivateLogicalDevice(), 1, &InFlightFence);

    uint32_t ImageAcquiredIndex = INVALID_INDEX;
    vkAcquireNextImageKHR(GetVkDevice()->GetPrivateLogicalDevice(), GetVkSwapChain()->GetPrivateSwapChain(), UINT64_MAX, ImageAvailableSemaphore, VK_NULL_HANDLE, &ImageAcquiredIndex);

    vkResetCommandBuffer(GetVkCommandBuffer()->GetPrivateCommandBuffer(), 0);

    GetVkCommandBuffer()->RecordRenderPassCommand(ImageAcquiredIndex);

    TArray<VkSemaphore> WaitSemaphores = {ImageAvailableSemaphore};
    TArray<VkSemaphore> SignalSemaphores = {RenderFinishedSemaphore};
    TArray<VkPipelineStageFlags> WaitStages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

    VkSubmitInfo SubmitInfo = {};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.waitSemaphoreCount = 1;



    SubmitInfo.pWaitSemaphores = WaitSemaphores.Data();
    SubmitInfo.pWaitDstStageMask = WaitStages.Data();

    SubmitInfo.commandBufferCount = 1;
    VkCommandBuffer CommandBuffer = GetVkCommandBuffer()->GetPrivateCommandBuffer();
    SubmitInfo.pCommandBuffers = &CommandBuffer;

    SubmitInfo.signalSemaphoreCount = 1;
    SubmitInfo.pSignalSemaphores = SignalSemaphores.Data();

    vkQueueSubmit(GetVkDevice()->GetGraphicsQueue(), 1, &SubmitInfo, InFlightFence);

    VkPresentInfoKHR PresentInfo = {};
    PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    PresentInfo.waitSemaphoreCount = 1;
    PresentInfo.pWaitSemaphores = SignalSemaphores.Data();

    TArray<VkSwapchainKHR> SwapChains = {GetVkSwapChain()->GetPrivateSwapChain()};
    PresentInfo.swapchainCount = 1;
    PresentInfo.pSwapchains = SwapChains.Data();
    PresentInfo.pImageIndices = &ImageAcquiredIndex;

    PresentInfo.pResults = nullptr;

    vkQueuePresentKHR(GetVkDevice()->GetPresentingQueue(), &PresentInfo);
}

VkInstance AVulkanRenderer::GetVkInstance() {
    return VulkanInstance;
}

FVulkanDevice* AVulkanRenderer::GetVkDevice() {
    return VulkanDevice;
}

FVulkanSwapChain* AVulkanRenderer::GetVkSwapChain() const {
    return VulkanSwapChain;
}

FVulkanSurface* AVulkanRenderer::GetVkSurface() const {
    return VulkanSurface;
}

FVulkanRenderPass* AVulkanRenderer::GetVkRenderPass() const {
    return VulkanRenderPass;
}

FVulkanGraphicsPipeline* AVulkanRenderer::GetVkGraphicsPipeline() const {
    return VulkanGraphicsPipeline;
}

FVulkanCommandBuffer* AVulkanRenderer::GetVkCommandBuffer() const {
    return VulkanCommandBuffer;
}

VkResult AVulkanRenderer::CreateInstance() {
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
        DebugMessengerCreateInfo.pfnUserCallback = FVulkanLogger::DebugCallback2;
        
        VkCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &DebugMessengerCreateInfo;
    }
    else {
        VkCreateInfo.enabledLayerCount = 0;
        VkCreateInfo.pNext = nullptr;
    }
    
    return vkCreateInstance(&VkCreateInfo, nullptr, &VulkanInstance);
}

VkResult AVulkanRenderer::CreateDebugMessenger() {
    VkResult Result = VK_SUCCESS;
    if (RunInDebug()) {
        VulkanLogger = new FVulkanLogger();
        Result = VulkanLogger->Init();
    }
    return Result;
}

void AVulkanRenderer::CleanDebugMessenger() {
    if (RunInDebug()) {
        VulkanLogger->Clean();
    }
}

VkResult AVulkanRenderer::CreateVulkanDevice() {
    VulkanDevice = new FVulkanDevice();
    return VulkanDevice->Init();
}

void AVulkanRenderer::CleanVulkanDevice() {
    VulkanDevice->Clean();
    delete VulkanDevice;
    VulkanDevice = nullptr;
}

VkResult AVulkanRenderer::CreateVulkanSurface() {
    VulkanSurface = new FVulkanSurface();
    return VulkanSurface->Init();
}

void AVulkanRenderer::CleanVulkanSurface() {
    VulkanSurface->Clean();
    delete VulkanSurface;
    VulkanSurface = nullptr;
}

VkResult AVulkanRenderer::CreateVulkanSwapChain() {
    VulkanSwapChain = new FVulkanSwapChain();
    return VulkanSwapChain->Init();
}

void AVulkanRenderer::CleanVulkanSwapChain() {
    VulkanSwapChain->Clean();
    delete VulkanSwapChain;
    VulkanSwapChain = nullptr;
}

VkResult AVulkanRenderer::CreateVulkanSwapChainImageViews() {
    return VulkanSwapChain->InitImageViews();
}

void AVulkanRenderer::CleanVulkanSwapChainImageViews() {
    VulkanSwapChain->CleanImageViews();
}

VkResult AVulkanRenderer::CreateVulkanFrameBuffers() {
    return VulkanSwapChain->InitFrameBuffers();
}

void AVulkanRenderer::CleanVulkanFrameBuffers() {
    VulkanSwapChain->CleanFrameBuffers();
}

VkResult AVulkanRenderer::CreateVulkanRenderPass() {
    VulkanRenderPass = new FVulkanRenderPass();
    return VulkanRenderPass->Init();
}

void AVulkanRenderer::CleanVulkanRenderPass() {
    VulkanRenderPass->Clean();
    delete VulkanRenderPass;
    VulkanRenderPass = nullptr;
}

VkResult AVulkanRenderer::CreateVulkanGraphicsPipeline() {
    VulkanGraphicsPipeline = new FVulkanGraphicsPipeline();
    return VulkanGraphicsPipeline->Init();
}

void AVulkanRenderer::CleanVulkanGraphicsPipeline() {
    VulkanGraphicsPipeline->Clean();
    delete VulkanGraphicsPipeline;
    VulkanGraphicsPipeline = nullptr;
}

VkResult AVulkanRenderer::CreateVulkanCommandBuffer() {
    VulkanCommandBuffer = new FVulkanCommandBuffer();
    return VulkanCommandBuffer->Init();
}

void AVulkanRenderer::CleanVulkanCommandBuffer() {
    VulkanCommandBuffer->Clean();
    delete VulkanCommandBuffer;
    VulkanCommandBuffer = nullptr;
}

VkResult AVulkanRenderer::CreateSyncObjects() {
    VkSemaphoreCreateInfo SemaphoreCreateInfo = {};
    SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo FenceCreateInfo = {};
    FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateSemaphore(GetVkDevice()->GetPrivateLogicalDevice(), &SemaphoreCreateInfo, nullptr, &ImageAvailableSemaphore);
    vkCreateSemaphore(GetVkDevice()->GetPrivateLogicalDevice(), &SemaphoreCreateInfo, nullptr, &RenderFinishedSemaphore);

    vkCreateFence(GetVkDevice()->GetPrivateLogicalDevice(), &FenceCreateInfo, nullptr, &InFlightFence);

    return VK_SUCCESS;
}

void AVulkanRenderer::CleanSyncObjects() {
    vkDestroySemaphore(GetVkDevice()->GetPrivateLogicalDevice(), ImageAvailableSemaphore, nullptr);
    vkDestroySemaphore(GetVkDevice()->GetPrivateLogicalDevice(), RenderFinishedSemaphore, nullptr);
    vkDestroyFence(GetVkDevice()->GetPrivateLogicalDevice(), InFlightFence, nullptr);
}

TArray<const char*> AVulkanRenderer::GetRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    return TArray<const char*>(Extensions);
}

bool AVulkanRenderer::RunInDebug() const {
    bool IsDebug = false;
#if IS_VULKAN_DEBUG
    IsDebug = true;
#endif
    return IsDebug;
}

