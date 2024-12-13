#pragma once
#include "../Component.h"
#include "../../../../Maths/Transforms/Transform.h"

class ASceneComponent : public AComponent{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASceneComponent, AComponent)
public:
    FTransform Transform;
};
