#pragma once
#include <GLFW/glfw3.h>
#include "../InpuManager.h"

class AOpenGLWindow;

enum EOpenGLInputType {
    EIT_KEYBOARD = 0,
    EIT_MOUSE_KEY = 1,
    EIT_MOUSE_MOTION = 2,
};

struct FOpenGLInputEvent {
    int KeyCode;
    int ActionType;
    EOpenGLInputType InputType;

    EInputState InputState() const;
};

class AOpenGLInputManager : public AInputManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AOpenGLInputManager, AInputManager);

    virtual void Init() override;

    virtual void HandleInputsEvents() override;

    void HandleOpenGLInputEvent(const FOpenGLInputEvent& Event);
    void UpdateCursorPosition(float PosX, float PosY);

    EKey OpenGLKeyboardCodeToAstralEngineKeyboardCode(int Key) const;
    int AstralEngineKeyboardCodeToOpenGLKeyboardCode(EKey Key) const;

    EKey OpenGLMouseKeyCodeToAstralEngineMouseKeyCode(int Key) const;
    int AstralEngineMouseKeyCodeToOpenGLMouseKeyCode(EKey Key) const;

    bool IsKeyInput(const FOpenGLInputEvent& Event) const;
    bool IsMotionInput(const FOpenGLInputEvent& Event) const;
    
private:
    AOpenGLWindow* GetActualWindow();

private:

    TMap<int, EKey> OpenGLKeyboardCodeLinkToAstralKeyboardCodeRegistry;
    TMap<EKey, int> AstralKeyboardCodeLinkToOpenGLKeyboardLinkRegistry;

    TMap<int, EKey> OpenGLMouseKeyCodeLinkToAstralMouseKeyCodeRegistry;
    TMap<EKey, int> AstralMouseKeyCodeLinkToOpenGLMouseKeyLinkRegistry;
};
