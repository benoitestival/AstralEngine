#pragma once
#include "../Renderer.h"
#include "vulkan/vulkan.h"


class FVulkanIndexBuffer;
class FVulkanPhysicalDevice;
class FVulkanVertexBuffer;
class AGLFWWindow;
class FVulkanLogger;
class FVulkanCommandBuffer;
class FVulkanGraphicsPipeline;
class FVulkanRenderPass;
class FVulkanSwapChain;
class FVulkanDevice;
class FVulkanSurface;

#define MANUAL_VULKAN_DEBUG 1;
#define IS_VULKAN_DEBUG IS_DEBUG && MANUAL_VULKAN_DEBUG;

class AVulkanRenderer : public ARenderer {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanRenderer, ARenderer)
    AVulkanRenderer();
    ~AVulkanRenderer() override;
    
    void Init() override;
    void DeInit() override;

    void Draw() override;

    void OnFrameBufferResize() override;
    
    VkInstance GetVkInstance();
    FVulkanDevice* GetVkDevice() const;
    FVulkanPhysicalDevice* GetVkPhysicalDevice() const;
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanSurface* GetVkSurface() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
    FVulkanVertexBuffer* GetVkVertexBuffer() const;
    FVulkanIndexBuffer* GetVkIndexBuffer() const;
    FVulkanCommandBuffer* GetVkCommandBuffer(int INDEX) const;
private:
    AGLFWWindow* GetWindow() const;
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

    VkResult ReCreateVulkanSwapChain();

    //Vulkan RenderPass methods
    VkResult CreateVulkanRenderPass();
    void CleanVulkanRenderPass();

    //Vulkan GraphicsPipeline methods
    VkResult CreateVulkanGraphicsPipeline();
    void CleanVulkanGraphicsPipeline();

    //Vulkan VertexBuffer
    VkResult CreateVulkanVertexBuffer();
    void CleanVulkanVertexBuffer();

    //Vulkan IndexBuffer
    VkResult CreateVulkanIndexBuffer();
    void CleanVulkanIndexBuffer();
    
    //Vulkan CommandBuffer methods
    VkResult CreateVulkanCommandBuffers();
    void CleanVulkanCommandBuffers();

    VkResult CreateSyncObjects();
    void CleanSyncObjects();
public:
    bool RunInDebug() const;
private:
    //bool CheckValidationLayerSupport();
    TArray<const char*> GetRequiredExtensions();
    //void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    
private:
    //Running Instance of Vulkan
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    
    FVulkanDevice* VulkanDevice = nullptr;
    FVulkanSurface* VulkanSurface = nullptr;
    FVulkanSwapChain* VulkanSwapChain = nullptr;
    FVulkanRenderPass* VulkanRenderPass = nullptr;
    FVulkanGraphicsPipeline* VulkanGraphicsPipeline = nullptr;
    FVulkanVertexBuffer* VulkanVertexBuffer = nullptr;
    FVulkanIndexBuffer* VulkanIndexBuffer = nullptr;
    TArray<FVulkanCommandBuffer*> VulkanCommandBuffers;
    
    FVulkanLogger* VulkanLogger = nullptr;

    //Sync Objects
    TArray<VkSemaphore> ImageAvailableSemaphores;
    TArray<VkSemaphore> RenderFinishedSemaphores;
    TArray<VkFence> InFlightFences;
private:
    const int MAX_FRAMES_IN_FLIGHT = 2;
    int CurrentFrameDrawn = 0;

    bool FrameBufferResized = false;
};
