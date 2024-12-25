#include "Shader.h"

#include <fstream>

AShader::AShader() {
}

AShader::~AShader() {
    
}

void AShader::LoadShader(const FPath& ShaderPath) {
    std::ifstream ShaderFile = std::ifstream(ShaderPath.ToString(), std::ios::ate | std::ios::binary);

    if (ShaderFile.is_open()) {
        int ShaderFileSize = ShaderFile.tellg();
        ShaderContent = TArray<char>(ShaderFileSize);

        ShaderFile.seekg(0);
        ShaderFile.read(ShaderContent.Data(), ShaderFileSize);

        ShaderFile.close();
    }
}

TArray<char>& AShader::GetShaderContent() {
    return ShaderContent;
}

int AShader::ContentSize() {
    return ShaderContent.Lenght();
}
