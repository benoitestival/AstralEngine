#include "VulkanShader.h"

#include "VulkanDevice.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../ShaderSystem/Shader.h"

FVulkanShader::FVulkanShader() : FVulkanShader(FPath()){
}

FVulkanShader::FVulkanShader(const FPath& ShaderPath) : ShaderDiskPath(ShaderPath) {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanShader::~FVulkanShader() {
}

VkResult FVulkanShader::Init() {
    VkResult Result = VK_ERROR_INITIALIZATION_FAILED;
    InternShader = NewObject<AShader>(AShader::StaticClass());
    if (InternShader != nullptr) {
        InternShader->LoadShader(ShaderDiskPath);

        VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
        ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ShaderModuleCreateInfo.codeSize = InternShader->ContentSize();
        ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(InternShader->GetShaderContent().Data());

        Result = vkCreateShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), &ShaderModuleCreateInfo, nullptr, &ShaderModule);
    }
    return Result;
}

void FVulkanShader::Clean() {
    vkDestroyShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), ShaderModule, nullptr);
    InternShader->Destroy();
}

VkShaderModule FVulkanShader::GetPrivateShader() {
    return ShaderModule;
}

AVulkanRenderManager* FVulkanShader::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanShader::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
