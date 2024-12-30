#pragma once
#include "../../Engine/CoreObjects/Objects/BaseObject.h"
#include "../../Utils/Path/Path.h"

class AShader : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AShader, ABaseObject)

    AShader();
    ~AShader() override;
    
    void LoadShader(const FPath& ShaderPath);
    virtual void CleanShader();
    TArray<char>& GetShaderContent();

    int ContentSize();
private:
    FPath ShaderDiskPath;
    TArray<char> ShaderContent;
};
