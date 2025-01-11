#include "VulkanPipelineLayout.h"

#include "VulkanDevice.h"
#include "../VulkanRenderer.h"
#include "../../../../Engine/Statics/GameplayStatics.h"

FVulkanPipelineLayout::FVulkanPipelineLayout() {
}

FVulkanPipelineLayout::~FVulkanPipelineLayout() {
}

VkResult FVulkanPipelineLayout::Init() {
    VkPipelineLayoutCreateInfo PipelineLayoutInfo = {};
    PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutInfo.setLayoutCount = 0; 
    PipelineLayoutInfo.pushConstantRangeCount = 0; 

    return vkCreatePipelineLayout(GetVkDevice()->GetPrivateRessource(), &PipelineLayoutInfo, nullptr, &GetPrivateRessource());
}

void FVulkanPipelineLayout::Clean() {
    vkDestroyPipelineLayout(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
}


FVulkanDevice* FVulkanPipelineLayout::GetVkDevice() const {
    return GetVKRenderer()->GetVkDevice();
}
