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
};

FInputValue::FInputValue() {
   ActualType = EInputValueType::EInputBool;
   InputBool = false;
}

FInputValue::FInputValue(EInputValueType DesiredType, EInputState InputState) {
   ActualType = DesiredType;
   if (DesiredType == EInputValueType::EInputBool) {
      InputBool = InputState == EInputState::Pressed ? true : false;
   }
   else if(DesiredType == EInputValueType::EInputAxis1D) {
      InputFloat = InputState == EInputState::Pressed ? 1.0f : 0.0f;
   }
}

TArray<EKey> InputUtils::GetKeys() {
   return Keys;
}
