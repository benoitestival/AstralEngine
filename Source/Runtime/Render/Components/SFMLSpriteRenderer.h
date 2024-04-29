#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "../../CoreObjects/Components/Implementations/PrimitiveComponent.h"

#define REGISTER_DRAWCALL(Sprite, ZOrder)\
    Cast<ASFMLRenderManager>(GameplayStatics::GetRenderManager())->RegisterSpriteDrawcall(Sprite, Transform, ZOrder);

class ASFMLSpriteRenderer : public APrimitiveComponent{
public:
    ASFMLSpriteRenderer();
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLSpriteRenderer, APrimitiveComponent)

    virtual void Tick(float DeltaTime) override;
private:
    sf::Sprite* Sprite;
};
