#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../../Utils/Array.h"
#include "../../../../../Utils/Path/Path.h"

class FVulkanPipelineLayout;
class FVulkanSwapChain;
class AVulkanShader;
class AVulkanRenderManager;
class FVulkanDevice;

class FVulkanGraphicsPipeline {
public:
    FVulkanGraphicsPipeline();
    ~FVulkanGraphicsPipeline();
    
    VkResult Init();
    void Clean();

private:
    TArray<VkPipelineShaderStageCreateInfo> CreateShaderStagesInfos();
    VkPipelineShaderStageCreateInfo CreatePipelineShaderStageInfos(VkShaderStageFlagBits Stage, AVulkanShader* Shader);
    VkPipelineDynamicStateCreateInfo CreatePipelineDynamicStateInfos();
    VkPipelineVertexInputStateCreateInfo  CreatePipelineVertexInputInfos();
    VkPipelineInputAssemblyStateCreateInfo CreatePipelineInputAssemblyInfos();
    VkPipelineViewportStateCreateInfo CreatePipelineViewportStateInfos(bool UseDynamicState = true);
    VkPipelineRasterizationStateCreateInfo CreatePipelineRasterizationStateInfos();
    VkPipelineMultisampleStateCreateInfo CreatePipelineMultisamplingStateInfos();
    VkPipelineColorBlendStateCreateInfo CreatePipelineColorBlendStateInfos();
private:
    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain();
private:
    AVulkanRenderManager* RenderManager = nullptr;

private:
    FVulkanPipelineLayout* VulkanPipelineLayout = nullptr;
};
