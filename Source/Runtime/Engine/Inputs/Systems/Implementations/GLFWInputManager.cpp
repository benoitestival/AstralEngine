// ReSharper disable All
#include "GLFWInputManager.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "../../../../Window/Implementations/GLFWWindow.h"
#include "../../../Engine/Engine.h"
#include "../../../Statics/GameplayStatics.h"
#include "../../../Time/TimerHandle.h"
#include "../../../Time/TimerManager.h"

EInputState FOpenGLKeyInputEvent::InputState() const {
    return ActionType == GLFW_RELEASE ? EInputState::Released : EInputState::Pressed;
}

void AOpenGLInputManager::Init() {
    AInputManager::Init();

    OpenGLKeyboardCodeLinkToAstralKeyboardCodeRegistry = {
        {GLFW_KEY_A, EKey::A},
        {GLFW_KEY_B, EKey::B},
        {GLFW_KEY_C, EKey::C},
        {GLFW_KEY_D, EKey::D},
        {GLFW_KEY_E, EKey::E},
        {GLFW_KEY_F, EKey::F},
        {GLFW_KEY_G, EKey::G},
        {GLFW_KEY_H, EKey::H},
        {GLFW_KEY_I, EKey::I},
        {GLFW_KEY_J, EKey::J},
        {GLFW_KEY_K, EKey::K},
        {GLFW_KEY_L, EKey::L},
        {GLFW_KEY_M, EKey::M},
        {GLFW_KEY_N, EKey::N},
        {GLFW_KEY_O, EKey::O},
        {GLFW_KEY_P, EKey::P},
        {GLFW_KEY_Q, EKey::Q},
        {GLFW_KEY_R, EKey::R},
        {GLFW_KEY_S, EKey::S},
        {GLFW_KEY_T, EKey::T},
        {GLFW_KEY_U, EKey::U},
        {GLFW_KEY_V, EKey::V},
        {GLFW_KEY_W, EKey::W},
        {GLFW_KEY_X, EKey::X},
        {GLFW_KEY_Y, EKey::Y},
        {GLFW_KEY_Z, EKey::Z},
        
        {GLFW_KEY_SPACE, EKey::SPACE},
        {GLFW_KEY_ESCAPE, EKey::ESCAPE},
        {GLFW_KEY_LEFT_CONTROL, EKey::LCTRL},
        {GLFW_KEY_RIGHT_CONTROL, EKey::RCTRL},
        {GLFW_KEY_LEFT_SHIFT, EKey::LSHIFT},
        {GLFW_KEY_RIGHT_SHIFT, EKey::RSHIFT},
        {GLFW_KEY_LEFT_ALT, EKey::LALT},
        {GLFW_KEY_RIGHT_ALT, EKey::RALT},
        
        {GLFW_KEY_0, EKey::NUMBER0},
        {GLFW_KEY_1, EKey::NUMBER1},
        {GLFW_KEY_2, EKey::NUMBER2},
        {GLFW_KEY_3, EKey::NUMBER3},
        {GLFW_KEY_4, EKey::NUMBER4},
        {GLFW_KEY_5, EKey::NUMBER5},
        {GLFW_KEY_6, EKey::NUMBER6},
        {GLFW_KEY_7, EKey::NUMBER7},
        {GLFW_KEY_8, EKey::NUMBER8},
        {GLFW_KEY_9, EKey::NUMBER9},
        
        {GLFW_KEY_TAB, EKey::TAB},
        {GLFW_KEY_ENTER, EKey::ENTER},
        {GLFW_KEY_BACKSPACE, EKey::BACKSPACE},
        
        {GLFW_KEY_UP, EKey::ARROWUP},
        {GLFW_KEY_DOWN, EKey::ARROWDOWN},
        {GLFW_KEY_RIGHT, EKey::ARROWLEFT},
        {GLFW_KEY_LEFT, EKey::ARROWRIGHT}
    };
    
    for (auto& Pair : OpenGLKeyboardCodeLinkToAstralKeyboardCodeRegistry) {
        AstralKeyboardCodeLinkToOpenGLKeyboardLinkRegistry.Insert(std::make_pair(Pair.second, Pair.first));
    }

    OpenGLMouseKeyCodeLinkToAstralMouseKeyCodeRegistry = {
        {GLFW_MOUSE_BUTTON_LEFT, EKey::MOUSEBUTTONLEFT},
        {GLFW_MOUSE_BUTTON_RIGHT, EKey::MOUSEBUTTONRIGHT},
        {GLFW_MOUSE_BUTTON_MIDDLE, EKey::MOUSEBUTTONMIDDLE}
    };

    for (auto& Pair : OpenGLMouseKeyCodeLinkToAstralMouseKeyCodeRegistry) {
        AstralMouseKeyCodeLinkToOpenGLMouseKeyLinkRegistry.Insert(std::make_pair(Pair.second, Pair.first));
    }
    
    GLFWwindow* PrivateWindow = GetActualWindow()->GetPrivateWindow();

    //Setup all callbacks for glfw inputs
    glfwSetKeyCallback(PrivateWindow, [](GLFWwindow* Window, int Key, int ScanCode, int ActionType, int Mods) {
        AOpenGLInputManager* InputManager = Cast<AOpenGLInputManager>(static_cast<AEngine*>(glfwGetWindowUserPointer(Window))->GetInputManager());
        InputManager->HandleOpenGLKeyInputEvent({Key, ActionType, EOpenGLInputType::EIT_KEYBOARD});
    });
    glfwSetMouseButtonCallback(PrivateWindow, [](GLFWwindow* Window, int MouseButton, int ActionType, int Mods) {
        AOpenGLInputManager* InputManager = Cast<AOpenGLInputManager>(static_cast<AEngine*>(glfwGetWindowUserPointer(Window))->GetInputManager());
        InputManager->HandleOpenGLKeyInputEvent({MouseButton, ActionType, EOpenGLInputType::EIT_MOUSE_KEY});
    });

    //Setup callback and settings for mouse motion 
    glfwSetCursorPosCallback(PrivateWindow, [](GLFWwindow* Window, double PosX, double PosY) {
        AOpenGLInputManager* InputManager = Cast<AOpenGLInputManager>(static_cast<AEngine*>(glfwGetWindowUserPointer(Window))->GetInputManager());
        //std::cout << InputManager->ListenMouseMotionCallBack << std::endl;
        if (InputManager->IsListeningForMouseMotionEvent()) {
            InputManager->HandleOpenGLMouseMotionEvent({{(float)PosX, (float)PosY}});
        }
    });
    if (glfwRawMouseMotionSupported()){
        glfwSetInputMode(PrivateWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    //Setup callback for scroll
    glfwSetScrollCallback(PrivateWindow, [](GLFWwindow* Window, double XOffset, double YOffset) {
        //TODO
    });

    
}

void AOpenGLInputManager::HandleInputsEvents(float DeltaTime) {
    AInputManager::HandleInputsEvents(DeltaTime);
    glfwPollEvents();

    /////////////KEYS/////////////////
    for (auto& Pair: ActiveInputs) {
        HandleKeyInput(Pair.first, FInputParams(Pair.second));
    }
    //Clear the releasing inputs
    ActiveInputs.RemoveValue(EInputState::Released);
    //////////////////////////////////

    //////////MOUSE MOTION////////////
    HandleKeyInput(EKey::MOUSEAXISXY, FInputParams(EInputState::Motion, MotionDirection));
    if (!IsMouseMoving()) {
        MotionDirection = {0.0f};//the mouse is not moving so we reset the motion
    }
}

void AOpenGLInputManager::HandleOpenGLKeyInputEvent(const FOpenGLKeyInputEvent& Event) {
    //Transforming from Opengl key code to Astral
    EKey AstralEngineKey = EKey::INVALID;
    if (Event.InputType == EOpenGLInputType::EIT_KEYBOARD) {
        AstralEngineKey = OpenGLKeyboardCodeToAstralEngineKeyboardCode(Event.KeyCode);
    }
    else if (Event.InputType == EOpenGLInputType::EIT_MOUSE_KEY) {
        AstralEngineKey = OpenGLMouseKeyCodeToAstralEngineMouseKeyCode(Event.KeyCode);
    }

    //Handling input state
    if (Event.InputState() == EInputState::Pressed && !ActiveInputs.Contains(AstralEngineKey)) {
        ActiveInputs.Insert({AstralEngineKey, EInputState::Pressed});
    }
    else if (Event.InputState() == EInputState::Released){
        ActiveInputs.Remove(AstralEngineKey);
        ActiveInputs.Insert({AstralEngineKey, EInputState::Released});
    }
}

void AOpenGLInputManager::HandleOpenGLMouseMotionEvent(const FOpenGLMouseMotionInputEvent& Event) {
    
    GameplayStatics::GetTimerManager()->UnregisterTimer(MouseMovementDetectionTimer);
    MouseMoving = true;
    
    FVector2D MouseMotionDirection = {0.0f};
    MouseMotionDirection.X() = Event.NewCoord.X() - PreviousCursorPosition.X();
    MouseMotionDirection.Y() = PreviousCursorPosition.Y() - Event.NewCoord.Y();//reverse because opengl Y is inverted

    MouseMotionDirection.SafeNormalize();

    MotionDirection = MouseMotionDirection;
    
    if (!GameplayStatics::ShowMouseCursor()) {
        ListenMouseMotionCallBack = false;
        SetCursorPosition(GetActualWindow()->GetWindowSize() * 0.5f);//if the cursor is hidden we put in back in the middle
        ListenMouseMotionCallBack = true;
    }
    
    PreviousCursorPosition = GetCursorPosition();
    MouseMovementDetectionTimer = GameplayStatics::GetTimerManager()->RegisterTimer(FTimerDelegate::FromLambda([this]() {
        MouseMoving = false;
    }), MouseDetectionTime);
}

FVector2D AOpenGLInputManager::GetCursorPosition() const {
    double CursorX = 0.0f;
    double CursorY = 0.0f;
    glfwGetCursorPos(GetActualWindow()->GetPrivateWindow(), &CursorX, &CursorY);
    FVector2D ActualCursorPosition = {(float)CursorX, (float)CursorY};
    return ActualCursorPosition;
}

void AOpenGLInputManager::SetCursorPosition(const FVector2D& Pos) {
    glfwSetCursorPos(GetActualWindow()->GetPrivateWindow(), Pos.X(), Pos.Y());
}

EKey AOpenGLInputManager::OpenGLKeyboardCodeToAstralEngineKeyboardCode(int Key) const {
    return OpenGLKeyboardCodeLinkToAstralKeyboardCodeRegistry.Find(Key);
}

int AOpenGLInputManager::AstralEngineKeyboardCodeToOpenGLKeyboardCode(EKey Key) const {
    return AstralKeyboardCodeLinkToOpenGLKeyboardLinkRegistry.Find(Key);
}

EKey AOpenGLInputManager::OpenGLMouseKeyCodeToAstralEngineMouseKeyCode(int Key) const {
    return OpenGLMouseKeyCodeLinkToAstralMouseKeyCodeRegistry.Find(Key);
}

int AOpenGLInputManager::AstralEngineMouseKeyCodeToOpenGLMouseKeyCode(EKey Key) const {
    return AstralMouseKeyCodeLinkToOpenGLMouseKeyLinkRegistry.Find(Key);
}

bool AOpenGLInputManager::IsListeningForMouseMotionEvent() {
    return ListenMouseMotionCallBack;
}

bool AOpenGLInputManager::IsMouseMoving() const {
    return MouseMoving;
}

AGLFWWindow* AOpenGLInputManager::GetActualWindow() const{
    return Cast<AGLFWWindow>(GameplayStatics::GetEngine()->GetActiveWindow());
}
