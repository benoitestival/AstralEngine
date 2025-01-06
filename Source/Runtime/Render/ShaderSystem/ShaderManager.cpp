#include "ShaderManager.h"

#include "Shader.h"
#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"


AShader* AShaderManager::CreateShaderFromPath(const FPath& ShaderPath, FClass* ShaderClass) {
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
