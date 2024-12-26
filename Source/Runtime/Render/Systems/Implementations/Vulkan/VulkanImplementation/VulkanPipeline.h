#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../../Utils/Path/Path.h"

class FVulkanSwapChain;
class FVulkanShader;
class AVulkanRenderManager;
class FVulkanDevice;

class FVulkanPipeline {
public:
    FVulkanPipeline();
    ~FVulkanPipeline();
    
    VkResult Init();
    void Clean();

private:
    FVulkanShader* CreateShader(const FPath& ShaderPath);
    void DestroyShader(FVulkanShader* Shader);

    VkPipelineShaderStageCreateInfo CreatePipelineShaderStageInfos(VkShaderStageFlagBits Stage, FVulkanShader* Shader);
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
};
