#include "ShaderManager.h"

#include <iostream>

#include "Shader.h"
#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "Vulkan/VulkanShader.h"


AShader* AShaderManager::CreateShaderFromPath(const FPath& ShaderPath, FClass* ShaderClass) {
    std::cout << ShaderPath.ToString() << std::endl;
    AShader* Shader = NewObject<AShader>(ShaderClass, this);
    Shader->LoadShader(ShaderPath);
    Shader->InitShader();
    return Shader;
}

void AShaderManager::ClearShaders() {
    for (auto& Shader : Shaders) {
        Shader->CleanShader();
    }
    Shaders.Clear();
}
