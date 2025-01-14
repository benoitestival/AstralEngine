#include "Renderer.h"

#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../ShaderSystem/ShaderManager.h"

void ARenderer::Init() {
    ShaderManager = NewObject<AShaderManager>(AShaderManager::StaticClass(), this);
    ShaderManager->Init();
}

void ARenderer::Draw() {
}

void ARenderer::Clear() {
}

void ARenderer::OnFrameBufferResize() {
}

AShaderManager* ARenderer::GetShaderManager() const {
    return ShaderManager;
}
