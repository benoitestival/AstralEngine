#include "SFMLStaticSpriteComponent.h"


ASFMLStaticSpriteComponent::ASFMLStaticSpriteComponent() {
    Sprite = nullptr;
}

void ASFMLStaticSpriteComponent::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (IsVisible) {
        REGISTER_DRAWCALL(0)
    }
}


