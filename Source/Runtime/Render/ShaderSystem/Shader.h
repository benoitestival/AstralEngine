#pragma once
#include "../../Engine/CoreObjects/Objects/BaseObject.h"
#include "../../Utils/Path/Path.h"

class AShader : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AShader, ABaseObject)

    AShader();
    ~AShader() override;
    
    void LoadShader(const FPath& ShaderPath);
    TArray<char>& GetShaderContent();

    int ContentSize();
private:
    TArray<char> ShaderContent;
};
