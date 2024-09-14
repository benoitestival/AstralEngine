#pragma once
#include "../Window.h"

class AOpenGLWindow : public AWindow{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AOpenGLWindow, AWindow)

    virtual void Construct() override;
};
