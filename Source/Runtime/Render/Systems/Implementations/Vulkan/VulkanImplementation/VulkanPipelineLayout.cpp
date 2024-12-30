#include "VulkanPipelineLayout.h"

#include "VulkanDevice.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"

FVulkanPipelineLayout::FVulkanPipelineLayout() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanPipelineLayout::~FVulkanPipelineLayout() {
}

VkResult FVulkanPipelineLayout::Init() {
    VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
    PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutInfo.setLayoutCount = 0; 
    PipelineLayoutInfo.pSetLayouts = nullptr; 
    PipelineLayoutInfo.pushConstantRangeCount = 0; 
    PipelineLayoutInfo.pPushConstantRanges = nullptr; 

    return vkCreatePipelineLayout(GetVkDevice()->GetPrivateLogicalDevice(), &PipelineLayoutInfo, nullptr, &PipelineLayout);
}

void FVulkanPipelineLayout::Clean() {
    vkDestroyPipelineLayout(GetVkDevice()->GetPrivateLogicalDevice(), PipelineLayout, nullptr);
}

VkPipelineLayout FVulkanPipelineLayout::GetPrivatePipelineLayout() const {
    return PipelineLayout;
}

AVulkanRenderManager* FVulkanPipelineLayout::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanPipelineLayout::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
