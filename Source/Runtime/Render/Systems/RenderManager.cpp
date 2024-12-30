#include "RenderManager.h"

#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../ShaderSystem/ShaderManager.h"

void ARenderManager::Init() {
    ShaderManager = NewObject<AShaderManager>(AShaderManager::StaticClass(), this);
    ShaderManager->Init();
}

void ARenderManager::Draw() {
}

void ARenderManager::Clear() {
}

AShaderManager* ARenderManager::GetShaderManager() const {
    return ShaderManager;
}
