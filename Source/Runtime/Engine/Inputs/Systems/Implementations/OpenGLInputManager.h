#pragma once
#include <GLFW/glfw3.h>
#include "../InpuManager.h"

class AOpenGLWindow;

class AOpenGLInputManager : public AInputManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AOpenGLInputManager, AInputManager);

    virtual void Init() override;

    virtual void HandleInputsEvents() override;

    void HandleOpenGLnputEvent();

private:
    AOpenGLWindow* GetActualWindow();

private:

    TMap<int, EKey> OpenGLKeyCodeLinkToAstralKeyCodeRegistry;
    TMap<EKey, int> AstralKeyCodeLinkToOpenGLKeyLinkRegistry;
};
