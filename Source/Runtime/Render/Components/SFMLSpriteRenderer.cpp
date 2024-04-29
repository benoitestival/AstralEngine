#include "SFMLSpriteRenderer.h"

#include "../../Statics/GameplayStatics.h"
#include "../../Utils/TemplateUtils.h"
#include "../Systems/Implementations/ASFMLRenderManager.h"

ASFMLSpriteRenderer::ASFMLSpriteRenderer() {
    Sprite = nullptr;
}

void ASFMLSpriteRenderer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (IsVisible) {
        REGISTER_DRAWCALL(Sprite, 0)
    }
}
