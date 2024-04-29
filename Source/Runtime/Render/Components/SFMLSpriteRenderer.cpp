#include "SFMLSpriteRenderer.h"

ASFMLSpriteRenderer::ASFMLSpriteRenderer() {
}

void ASFMLSpriteRenderer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (IsVisible) {
        REGISTER_DRAWCALL();
    }
}
