#include "OpenGLInputManager.h"

#include <GLFW/glfw3.h>

#include "../../../../Window/Implementations/OpenGLWindow.h"
#include "../../../Engine/Engine.h"
#include "../../../Statics/GameplayStatics.h"

EInputState FOpenGLInputEvent::InputState() const {
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
        InputManager->HandleOpenGLInputEvent({Key, ActionType, EOpenGLInputType::EIT_KEYBOARD});
    });
    glfwSetMouseButtonCallback(PrivateWindow, [](GLFWwindow* Window, int MouseButton, int ActionType, int Mods) {
        AOpenGLInputManager* InputManager = Cast<AOpenGLInputManager>(static_cast<AEngine*>(glfwGetWindowUserPointer(Window))->GetInputManager());
        InputManager->HandleOpenGLInputEvent({MouseButton, ActionType, EOpenGLInputType::EIT_MOUSE_KEY});
    });
    
    glfwSetCursorPosCallback(PrivateWindow, [](GLFWwindow* Window, double PosX, double PosY) {
        AOpenGLInputManager* InputManager = Cast<AOpenGLInputManager>(static_cast<AEngine*>(glfwGetWindowUserPointer(Window))->GetInputManager());
        InputManager->UpdateCursorPosition((float)PosX, (float)PosY);
    });
    glfwSetScrollCallback(PrivateWindow, [](GLFWwindow* Window, double XOffset, double YOffset) {
        //TODO

    });
}

void AOpenGLInputManager::HandleInputsEvents() {
    AInputManager::HandleInputsEvents();
    glfwPollEvents();
}

void AOpenGLInputManager::HandleOpenGLInputEvent(const FOpenGLInputEvent& Event) {
    if (IsKeyInput(Event)) {
        EKey AstralEngineKey = EKey::INVALID;
        if (Event.InputType == EOpenGLInputType::EIT_KEYBOARD) {
            AstralEngineKey = OpenGLKeyboardCodeToAstralEngineKeyboardCode(Event.KeyCode);
            HandleKeyInput(AstralEngineKey, Event.InputState());
        }
        else if (Event.InputType == EOpenGLInputType::EIT_MOUSE_KEY) {
            AstralEngineKey = OpenGLMouseKeyCodeToAstralEngineMouseKeyCode(Event.KeyCode);
            HandleKeyInput(AstralEngineKey, Event.InputState());
        }
    }
}

void AOpenGLInputManager::UpdateCursorPosition(float PosX, float PosY) {
    CursorPosition = {PosX, PosY};
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


bool AOpenGLInputManager::IsKeyInput(const FOpenGLInputEvent& Event) const {
    return true;
}

bool AOpenGLInputManager::IsMotionInput(const FOpenGLInputEvent& Event) const {
    return false;
}

AOpenGLWindow* AOpenGLInputManager::GetActualWindow() {
    return Cast<AOpenGLWindow>(GameplayStatics::GetEngine()->GetActiveWindow());
}
