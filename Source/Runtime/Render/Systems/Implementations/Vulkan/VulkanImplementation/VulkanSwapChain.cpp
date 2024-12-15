#include "VulkanSwapChain.h"

#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

FVulkanSwapChain::FVulkanSwapChain() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanSwapChain::~FVulkanSwapChain() {
}

VkResult FVulkanSwapChain::Init() {
}

void FVulkanSwapChain::Clean() {
}

AVulkanRenderManager* FVulkanSwapChain::GetRenderManager() const {
    return RenderManager;
}
