#include "InputAction.h"

bool AInputAction::ShouldExecuteKeyboardAction(EKey Key, EKeyboardKeyState KeyState) const {
    return Key == LinkedKey;
}

void AInputAction::ExecuteKeyboardAction(EKey Key, EKeyboardKeyState KeyState) {
    if (LinkedKeyState == EKeyboardKeyState::Released && KeyState == EKeyboardKeyState::Pressed) {
        OnInputStart.BroadCast(Key, this);
    }

    if (KeyState == EKeyboardKeyState::Pressed) {
        OnInputTrigger.BroadCast(Key, this);
    }

    if (LinkedKeyState == EKeyboardKeyState::Pressed && KeyState == EKeyboardKeyState::Released) {
        OnInputStop.BroadCast(Key, this);
    }

    LinkedKeyState = KeyState;
}