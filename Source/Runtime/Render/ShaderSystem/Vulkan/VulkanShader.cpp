#include "VulkanShader.h"

#include "../../../Engine/Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../RenderAPIs/Vulkan/VulkanRenderer.h"
#include "../../RenderAPIs/Vulkan/VulkanClasses/VulkanDevice/VulkanDevice.h"


AVulkanShader::AVulkanShader(){
    RenderManager = Cast<AVulkanRenderer>(GameplayStatics::GetRenderManager());
}

AVulkanShader::~AVulkanShader() {
}

void AVulkanShader::InitShader() {
    AShader::InitShader();

    VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
    ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ShaderModuleCreateInfo.codeSize = ContentSize();
    ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(GetShaderContent().Data());

    vkCreateShaderModule(GetVkDevice()->GetPrivateRessource(), &ShaderModuleCreateInfo, nullptr, &ShaderModule);
}

void AVulkanShader::CleanShader() {
    AShader::CleanShader();
    vkDestroyShaderModule(GetVkDevice()->GetPrivateRessource(), ShaderModule, nullptr);
}

VkShaderModule AVulkanShader::GetPrivateShader() {
    return ShaderModule;
}

AVulkanRenderer* AVulkanShader::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* AVulkanShader::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
