#pragma once
#include "../../Engine/CoreObjects/Managers/Manager.h"
#include "../../Utils/Path/Path.h"

class AShader;

class AShaderManager : public AManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AShaderManager, AManager)

    AShader* CreateShaderFromPath(const FPath& ShaderPath, FClass* ShaderClass);
    template<class ShaderClass>
    ShaderClass* CreateShaderFromPath(const FPath& ShaderPath) {
        return Cast<ShaderClass>(CreateShaderFromPath(ShaderPath, ShaderClass::StaticClass()));
    }

    void ClearShaders();
private:
    TArray<AShader*> Shaders;
};
