#pragma once
#include "../../Engine/CoreObjects/Managers/Manager.h"
#include "../../Engine/CoreObjects/Objects/BaseObject.h"

class AShaderManager;

class ARenderer : public AManager{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ARenderer, AManager)

    virtual void Init() override;
    
    virtual void Draw();
    virtual void Clear();

    AShaderManager* GetShaderManager() const;
private:
    AShaderManager* ShaderManager = nullptr;
};
