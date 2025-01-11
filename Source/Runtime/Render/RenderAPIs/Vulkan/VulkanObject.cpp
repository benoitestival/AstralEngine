#include "VulkanObject.h"

#include "../../../Engine/Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"

FVulkanObject::FVulkanObject() {
    Renderer = Cast<AVulkanRenderer>(GameplayStatics::GetRenderManager());
}

VkResult FVulkanObject::Init() {
    return VK_SUCCESS;
}

void FVulkanObject::Clean() {
    
}

AVulkanRenderer* FVulkanObject::GetVKRenderer() const {
    return Renderer;
}
