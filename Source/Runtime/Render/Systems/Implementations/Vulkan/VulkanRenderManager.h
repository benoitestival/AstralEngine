#pragma once
#include "vulkan/vulkan.h"
#include "../../RenderManager.h"


class FVulkanLogger;
class FVulkanCommandBuffer;
class FVulkanGraphicsPipeline;
class FVulkanRenderPass;
class FVulkanSwapChain;
class FVulkanDevice;
class FVulkanSurface;

#define MANUAL_VULKAN_DEBUG 0;
#define IS_VULKAN_DEBUG IS_DEBUG && MANUAL_VULKAN_DEBUG;

class AVulkanRenderManager : public ARenderManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanRenderManager, ARenderManager)
    AVulkanRenderManager();
    ~AVulkanRenderManager() override;
    
    void Init() override;
    void DeInit() override;

    void Draw() override;
    
    VkInstance GetVkInstance();
    FVulkanDevice* GetVkDevice();
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanSurface* GetVkSurface() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
    FVulkanCommandBuffer* GetVkCommandBuffer() const;
private:
    //Instance Methods
    VkResult CreateInstance();

    VkResult CreateDebugMessenger();
    void CleanDebugMessenger();
    
    //Vulkan Device Methods
    VkResult CreateVulkanDevice();
    void CleanVulkanDevice();
    
    //Vulkan Surface methods
    VkResult CreateVulkanSurface();
    void CleanVulkanSurface();

    //Vulkan SwapChain methods
    VkResult CreateVulkanSwapChain();
    void CleanVulkanSwapChain();
    VkResult CreateVulkanSwapChainImageViews();
    void CleanVulkanSwapChainImageViews();
    VkResult CreateVulkanFrameBuffers();
    void CleanVulkanFrameBuffers();

    //Vulkan RenderPass methods
    VkResult CreateVulkanRenderPass();
    void CleanVulkanRenderPass();

    //Vulkan GraphicsPipeline methods
    VkResult CreateVulkanGraphicsPipeline();
    void CleanVulkanGraphicsPipeline();

    //Vulkan CommandBuffer methods
    VkResult CreateVulkanCommandBuffer();
    void CleanVulkanCommandBuffer();

    VkResult CreateSyncObjects();
    void CleanSyncObjects();

private:
    //bool CheckValidationLayerSupport();
    TArray<const char*> GetRequiredExtensions();
    //void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    bool RunInDebug() const;
private:
    //Running Instance of Vulkan
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    
    FVulkanDevice* VulkanDevice = nullptr;
    FVulkanSurface* VulkanSurface = nullptr;
    FVulkanSwapChain* VulkanSwapChain = nullptr;
    FVulkanRenderPass* VulkanRenderPass = nullptr;
    FVulkanGraphicsPipeline* VulkanGraphicsPipeline = nullptr;
    FVulkanCommandBuffer* VulkanCommandBuffer = nullptr;
    
    FVulkanLogger* VulkanLogger = nullptr;

    //Sync Objects
    VkSemaphore ImageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore RenderFinishedSemaphore = VK_NULL_HANDLE;
    VkFence InFlightFence = VK_NULL_HANDLE;

    // VkDebugUtilsMessengerEXT DebugMessenger = VK_NULL_HANDLE;
    // TArray<const char*> ValidationLayers = {
    //     "VK_LAYER_KHRONOS_validation"
    // };

// #ifdef IS_DEBUG
//     const bool UseValidationLayers = true;
// #else
//     const bool UseValidationLayers = false;
// #endif
};
