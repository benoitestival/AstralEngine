#pragma once
#include "../../Engine/CoreObjects/Objects/BaseObject.h"

class ARenderManager : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ARenderManager, ABaseObject)

    virtual void Draw();
    virtual void Clear();
};
