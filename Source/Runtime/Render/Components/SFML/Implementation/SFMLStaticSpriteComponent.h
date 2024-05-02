#pragma once

#include "../SFMLSpriteComponent.h"


class ASFMLStaticSpriteComponent : public ASFMLSpriteComponent{
public:
    ASFMLStaticSpriteComponent();
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLStaticSpriteComponent, ASFMLSpriteComponent)

    virtual void Tick(float DeltaTime) override;
private:
    sf::Sprite* Sprite;
};
