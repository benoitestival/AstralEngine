#pragma once
#include "vulkan/vulkan.h"
#include "../../RenderManager.h"


class FVulkanGraphicsPipeline;
class FVulkanRenderPass;
class FVulkanSwapChain;
class FVulkanDevice;
class FVulkanSurface;



class AVulkanRenderManager : public ARenderManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanRenderManager, ARenderManager)
    AVulkanRenderManager();
    ~AVulkanRenderManager() override;
    
    void Init() override;
    void DeInit() override;

    VkInstance GetVkInstance();
    FVulkanDevice* GetVkDevice();
    FVulkanSwapChain* GetVkSwapChain() const;
    FVulkanSurface* GetVkSurface() const;
    FVulkanRenderPass* GetVkRenderPass() const;
    FVulkanGraphicsPipeline* GetVkGraphicsPipeline() const;
private:
    //Instance Methods
    VkResult CreateInstance();

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

    //Vulkan RenderPass methods
    VkResult CreateVulkanRenderPass();
    void CleanVulkanRenderPass();

    //Vulkan GraphicsPipeline methods
    VkResult CreateVulkanGraphicsPipeline();
    void CleanVulkanGraphicsPipeline();
private:
    //Running Instance of Vulkan
    VkInstance VulkanInstance = VK_NULL_HANDLE;
    
    FVulkanDevice* VulkanDevice = nullptr;
    FVulkanSurface* VulkanSurface = nullptr;
    FVulkanSwapChain* VulkanSwapChain = nullptr;
    FVulkanRenderPass* VulkanRenderPass = nullptr;
    FVulkanGraphicsPipeline* VulkanGraphicsPipeline = nullptr;
};
