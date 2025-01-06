#include "Shader.h"

#include <fstream>

AShader::AShader() {
}

AShader::~AShader() {
    
}

void AShader::LoadShader(const FPath& ShaderPath) {
    ShaderDiskPath = ShaderPath;
    std::ifstream ShaderFile = std::ifstream(ShaderDiskPath.ToString(), std::ios::ate | std::ios::binary);

    if (ShaderFile.is_open()) {
        int ShaderFileSize = ShaderFile.tellg();
        ShaderContent = TArray<char>(ShaderFileSize);

        ShaderFile.seekg(0);
        ShaderFile.read(ShaderContent.Data(), ShaderFileSize);
        
        ShaderFile.close();
    }
}

void AShader::InitShader() {
}

void AShader::CleanShader() {
    ShaderContent.Clear();
}

TArray<char>& AShader::GetShaderContent() {
    return ShaderContent;
}

int AShader::ContentSize() {
    return ShaderContent.Lenght();
}
