#pragma once
#include <GLFW/glfw3.h>
#include "../InpuManager.h"

class AOpenGLWindow;

enum EOpenGLInputType {
    EIT_KEYBOARD = 0,
    EIT_MOUSE_KEY = 1,
    EIT_MOUSE_MOTION = 2,
};

struct FOpenGLKeyInputEvent {
    int KeyCode;
    int ActionType;
    EOpenGLInputType InputType;

    EInputState InputState() const;
};

struct FOpenGLMouseMotionInputEvent {
    FVector2D NewCoord;
    FVector2D OldCoord;
};

class AOpenGLInputManager : public AInputManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AOpenGLInputManager, AInputManager);

    virtual void Init() override;

    virtual void HandleInputsEvents(float DeltaTime) override;

    void HandleOpenGLKeyInputEvent(const FOpenGLKeyInputEvent& Event);
    void HandleOpenGLMouseMotionEvent(const FOpenGLMouseMotionInputEvent& Event);
    virtual FVector2D GetCursorPosition() const override;
    virtual void SetCursorPosition(const FVector2D& Pos) override;
    
    EKey OpenGLKeyboardCodeToAstralEngineKeyboardCode(int Key) const;
    int AstralEngineKeyboardCodeToOpenGLKeyboardCode(EKey Key) const;

    EKey OpenGLMouseKeyCodeToAstralEngineMouseKeyCode(int Key) const;
    int AstralEngineMouseKeyCodeToOpenGLMouseKeyCode(EKey Key) const;

    bool IsListeningForMouseMotionEvent();
private:
    bool IsMouseMoving() const;
    AOpenGLWindow* GetActualWindow() const;

private:

    TMap<EKey, EInputState> ActiveInputs;

    ///////MOUSE MOTION///////
    FVector2D MotionDirection;
    FVector2D PreviousCursorPosition;
    bool ListenMouseMotionCallBack = false;
    /////////////////////////
    
    TMap<int, EKey> OpenGLKeyboardCodeLinkToAstralKeyboardCodeRegistry;
    TMap<EKey, int> AstralKeyboardCodeLinkToOpenGLKeyboardLinkRegistry;

    TMap<int, EKey> OpenGLMouseKeyCodeLinkToAstralMouseKeyCodeRegistry;
    TMap<EKey, int> AstralMouseKeyCodeLinkToOpenGLMouseKeyLinkRegistry;
};
