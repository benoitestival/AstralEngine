#include "InputUtils.h"
TArray<EKey> InputUtils::Keys = {
   EKey::A,
   EKey::B,
   EKey::C,
   EKey::D,
   EKey::E,
   EKey::F,
   EKey::G,
   EKey::H,
   EKey::I,
   EKey::J,
   EKey::K,
   EKey::L,
   EKey::M,
   EKey::N,
   EKey::O,
   EKey::P,
   EKey::Q,
   EKey::R,
   EKey::S,
   EKey::T,
   EKey::U,
   EKey::V,
   EKey::W,
   EKey::X,
   EKey::Y,
   EKey::Z,
   EKey::SPACE,
   EKey::ESCAPE,
   EKey::LCTRL,
   EKey::RCTRL,
   EKey::LSHIFT,
   EKey::RSHIFT,
   EKey::LALT,
   EKey::RALT,
   EKey::NUMBER0,
   EKey::NUMBER1,
   EKey::NUMBER2,
   EKey::NUMBER3,
   EKey::NUMBER4,
   EKey::NUMBER5,
   EKey::NUMBER6,
   EKey::NUMBER7,
   EKey::NUMBER8,
   EKey::NUMBER9,
   EKey::TAB,
   EKey::ENTER,
   EKey::BACKSPACE,
   EKey::ARROWUP,
   EKey::ARROWDOWN,
   EKey::ARROWRIGHT,
   EKey::ARROWLEFT,

   EKey::MOUSEBUTTONLEFT,
   EKey::MOUSEBUTTONRIGHT,
   EKey::MOUSEBUTTONMIDDLE,

   EKey::MOUSEAXISX,
   EKey::MOUSEAXISY,
   EKey::MOUSEAXISXY,
};

FInputParams::FInputParams() {
   InputState = EInputState::Released;
   InputValue = {0.0f};
}

FInputParams::FInputParams(EInputState State) {
   InputState = State;
   InputValue = {0.0f};
}

FInputParams::FInputParams(EInputState State, bool Value) {
   InputState = State;
   if (Value) {
      InputValue = {1.0f};
   }
   else {
      InputValue = {0.0f};

   }
}

FInputParams::FInputParams(EInputState State, float Value) {
   InputState = State;
   InputValue = {Value, 0.0f};
}

FInputParams::FInputParams(EInputState State, const FVector2D& Value) {
   InputState = State;
   InputValue = Value;
}

FInputValue::FInputValue() {
   ActualType = EInputValueType::EInputBool;
   InputBool = false;
}

FInputValue::FInputValue(EInputValueType DesiredType, FInputParams InputParams) {
   ActualType = DesiredType;
   if (DesiredType == EInputValueType::EInputBool) {
      InputBool = InputUtils::IsInputActive(InputParams.InputState) ? true : false;
   }
   else if(DesiredType == EInputValueType::EInputAxis1D) {
      InputFloat = InputParams.InputValue.X;
   }
   else if(DesiredType == EInputValueType::EInputAxis2D) {
      InputVector2D = InputParams.InputValue;
   }
}

TArray<EKey> InputUtils::GetKeys() {
   return Keys;
}

bool InputUtils::IsInputActive(EInputState InputState) {
   return InputState == EInputState::Pressed || InputState == EInputState::Motion;
}

bool InputUtils::IsInputInactive(EInputState InputState) {
   return InputState == EInputState::Released;
}
