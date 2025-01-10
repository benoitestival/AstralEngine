#include "VulkanShader.h"

#include "../../../Engine/Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../RenderAPIs/Implementations/Vulkan/VulkanRenderManager.h"
#include "../../RenderAPIs/Implementations/Vulkan/VulkanImplementation/VulkanDevice.h"
#include "../../RenderAPIs/Implementations/Vulkan/VulkanImplementation/Test/VulkanClass.h"


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

    vkCreateShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), &ShaderModuleCreateInfo, nullptr, &ShaderModule);
}

void AVulkanShader::CleanShader() {
    AShader::CleanShader();
    vkDestroyShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), ShaderModule, nullptr);
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
