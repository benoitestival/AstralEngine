﻿#pragma once
#include "../../Engine/CoreObjects/Managers/Manager.h"
#include "../../Engine/CoreObjects/Objects/BaseObject.h"

class ARenderManager : public AManager{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ARenderManager, AManager)

    virtual void Init() override;
    
    virtual void Draw();
    virtual void Clear();
};
