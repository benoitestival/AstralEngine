#pragma once
#include <vulkan/vulkan_core.h>

#include "../VulkanObject.h"
#include "../../../../Utils/Array.h"
#include "../VulkanHelpers/VulkanRessource.h"


class FVulkanRenderPass;
class FVulkanPipelineLayout;
class FVulkanSwapChain;
class AVulkanShader;
class AVulkanRenderer;
class FVulkanDevice;

class FVulkanGraphicsPipeline : public FVulkanObject, public TVulkanRessource<VkPipeline>{
public:
    FVulkanGraphicsPipeline();
    ~FVulkanGraphicsPipeline() override;
    
    virtual VkResult Init() override;
    virtual void Clean() override;
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
    FVulkanDevice* GetVkDevice() const;
    FVulkanSwapChain* GetVkSwapChain();
    FVulkanRenderPass* GetVkRenderPass() const;

private:
    VkPipelineLayout Test = VK_NULL_HANDLE;
    FVulkanPipelineLayout* VulkanPipelineLayout = nullptr;
    TArray<VkDynamicState> DynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
};
