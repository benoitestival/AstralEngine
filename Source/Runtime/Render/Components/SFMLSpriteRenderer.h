#pragma once
#include "../../CoreObjects/Components/Implementations/PrimitiveComponent.h"

#define REGISTER_DRAWCALL()


class ASFMLSpriteRenderer : public APrimitiveComponent{
public:
    ASFMLSpriteRenderer();
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLSpriteRenderer, APrimitiveComponent)

    virtual void Tick(float DeltaTime) override;
private:
};
