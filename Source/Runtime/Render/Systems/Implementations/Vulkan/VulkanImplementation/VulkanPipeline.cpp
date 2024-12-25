#include "VulkanPipeline.h"

#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

FVulkanPipeline::FVulkanPipeline() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanPipeline::~FVulkanPipeline() {
}

VkResult FVulkanPipeline::Init() {
    return VK_SUCCESS;
}

void FVulkanPipeline::Clean() {
}

AVulkanRenderManager* FVulkanPipeline::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanPipeline::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
