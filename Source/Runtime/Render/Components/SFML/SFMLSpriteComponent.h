#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "../../../CoreObjects/Components/Implementations/PrimitiveComponent.h"
#include "../../../Statics/GameplayStatics.h"
#include "../../Systems/Implementations/ASFMLRenderManager.h"
#include "../../../Utils/TemplateUtils.h"
#define REGISTER_DRAWCALL(ZOrder)\
    Cast<ASFMLRenderManager>(GameplayStatics::GetRenderManager())->RegisterSpriteDrawcall(this, ZOrder);


class ASFMLSpriteComponent : public APrimitiveComponent{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLSpriteComponent, APrimitiveComponent)
};
