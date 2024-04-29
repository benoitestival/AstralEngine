#pragma once
#include "SceneComponent.h"

class APrimitiveComponent : ASceneComponent {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(APrimitiveComponent, ASceneComponent)

public:
    bool IsVisible = true;
};
