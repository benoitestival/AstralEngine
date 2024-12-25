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
    InterShader = NewObject<AShader>(AShader::StaticClass());
    if (InterShader != nullptr) {
        InterShader->LoadShader(ShaderDiskPath);

        VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
        ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ShaderModuleCreateInfo.codeSize = InterShader->ContentSize();
        ShaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(InterShader->GetShaderContent().Data());

        Result = vkCreateShaderModule(GetVkDevice()->GetPrivateLogicalDevice(), &ShaderModuleCreateInfo, nullptr, &ShaderModule);
    }
    return Result;
}

void FVulkanShader::Clean() {
}

AVulkanRenderManager* FVulkanShader::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanShader::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
