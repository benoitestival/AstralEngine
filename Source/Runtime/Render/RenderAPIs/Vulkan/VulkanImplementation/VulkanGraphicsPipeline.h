#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../Utils/Array.h"


class FVulkanRenderPass;
class FVulkanPipelineLayout;
class FVulkanSwapChain;
class AVulkanShader;
class AVulkanRenderer;
class FVulkanDevice;

class FVulkanGraphicsPipeline {
public:
    FVulkanGraphicsPipeline();
    ~FVulkanGraphicsPipeline();
    
    VkResult Init();
    void Clean();
    VkPipeline GetPrivateGraphicsPipeline();
private:
    TArray<VkPipelineShaderStageCreateInfo> CreateShaderStagesInfos();
    VkPipelineShaderStageCreateInfo CreatePipelineShaderStageInfos(VkShaderStageFlagBits Stage, AVulkanShader* Shader);
    VkPipelineVertexInputStateCreateInfo  CreatePipelineVertexInputInfos();
    VkPipelineInputAssemblyStateCreateInfo CreatePipelineInputAssemblyInfos();
    VkPipelineViewportStateCreateInfo CreatePipelineViewportStateInfos(bool UseDynamicState = true);
    VkPipelineRasterizationStateCreateInfo CreatePipelineRasterizationStateInfos();
    VkPipelineMultisampleStateCreateInfo CreatePipelineMultisamplingStateInfos();
    VkPipelineColorBlendAttachmentState CreatePipelineColorBlendAttachmentsState();
    VkPipelineColorBlendStateCreateInfo CreatePipelineColorBlendStateInfos();
    VkPipelineDynamicStateCreateInfo CreatePipelineDynamicStateInfos();

    FVulkanPipelineLayout* CreatePipelineLayout();
    void CleanPipelineLayout();
private:
    AVulkanRenderer* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain();
    FVulkanRenderPass* GetVkRenderPass() const;
private:
    VkPipeline GraphicsPipeline = VK_NULL_HANDLE;
    AVulkanRenderer* RenderManager = nullptr;

private:
    FVulkanPipelineLayout* VulkanPipelineLayout = nullptr;

    TArray<VkDynamicState> DynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
};
