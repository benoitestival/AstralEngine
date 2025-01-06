#include "VulkanShader.h"

#include "../../../Engine/Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../Systems/Implementations/Vulkan/VulkanRenderManager.h"
#include "../../Systems/Implementations/Vulkan/VulkanImplementation/VulkanDevice.h"


AVulkanShader::AVulkanShader(){
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

AVulkanShader::~AVulkanShader() {
}

void AVulkanShader::InitShader() {
    AShader::InitShader();

    VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
    ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ShaderModuleCreateInfo.codeSize = ContentSize();
    ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(GetShaderContent().Data());

    vkCreateShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), &ShaderModuleCreateInfo, nullptr, &ShaderModule);
}

void AVulkanShader::CleanShader() {
    AShader::CleanShader();
    vkDestroyShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), ShaderModule, nullptr);
}

VkShaderModule AVulkanShader::GetPrivateShader() {
    return ShaderModule;
}

AVulkanRenderManager* AVulkanShader::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* AVulkanShader::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
