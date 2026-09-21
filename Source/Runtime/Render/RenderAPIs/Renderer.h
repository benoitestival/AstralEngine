#pragma once
#include "../../Engine/CoreObjects/Systems/EngineSystem.h"
#include "../../Engine/CoreObjects/Objects/BaseObject.h"

class AShaderManager;

class ARenderer : public AEngineSystem{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ARenderer, AEngineSystem)

    virtual void Init() override;
    
    virtual void Draw();
    virtual void Clear();

    virtual void OnFrameBufferResize();
    
    AShaderManager* GetShaderManager() const;
private:
    AShaderManager* ShaderManager = nullptr;
};
