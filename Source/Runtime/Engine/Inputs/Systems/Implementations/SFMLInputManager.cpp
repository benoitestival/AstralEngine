// #include "SFMLInputManager.h"
//
// #include <SFML/Graphics/RenderWindow.hpp>
//
// #include "../../../../Window/Implementations/SFMLWindow.h"
// #include "../../../Engine/Engine.h"
// #include "../../../Statics/GameplayStatics.h"
//
// void ASFMLInputManager::Init() {
//     Super::Init();
//     SFMLKeyCodeLinkToAstralKeyCodeRegistry = {
//         {sf::Keyboard::Key::A, EKey::A},
//         {sf::Keyboard::Key::B, EKey::B},
//         {sf::Keyboard::Key::C, EKey::C},
//         {sf::Keyboard::Key::D, EKey::D},
//         {sf::Keyboard::Key::E, EKey::E},
//         {sf::Keyboard::Key::F, EKey::F},
//         {sf::Keyboard::Key::G, EKey::G},
//         {sf::Keyboard::Key::H, EKey::H},
//         {sf::Keyboard::Key::I, EKey::I},
//         {sf::Keyboard::Key::J, EKey::J},
//         {sf::Keyboard::Key::K, EKey::K},
//         {sf::Keyboard::Key::L, EKey::L},
//         {sf::Keyboard::Key::M, EKey::M},
//         {sf::Keyboard::Key::N, EKey::N},
//         {sf::Keyboard::Key::O, EKey::O},
//         {sf::Keyboard::Key::P, EKey::P},
//         {sf::Keyboard::Key::Q, EKey::Q},
//         {sf::Keyboard::Key::R, EKey::R},
//         {sf::Keyboard::Key::S, EKey::S},
//         {sf::Keyboard::Key::T, EKey::T},
//         {sf::Keyboard::Key::U, EKey::U},
//         {sf::Keyboard::Key::V, EKey::V},
//         {sf::Keyboard::Key::W, EKey::W},
//         {sf::Keyboard::Key::X, EKey::X},
//         {sf::Keyboard::Key::Y, EKey::Y},
//         {sf::Keyboard::Key::Z, EKey::Z},
//         
//         {sf::Keyboard::Key::Space, EKey::SPACE},
//         {sf::Keyboard::Key::Escape, EKey::ESCAPE},
//         {sf::Keyboard::Key::LControl, EKey::LCTRL},
//         {sf::Keyboard::Key::RControl, EKey::RCTRL},
//         {sf::Keyboard::Key::LShift, EKey::LSHIFT},
//         {sf::Keyboard::Key::RShift, EKey::RSHIFT},
//         {sf::Keyboard::Key::LAlt, EKey::LALT},
//         {sf::Keyboard::Key::RAlt, EKey::RALT},
//         
//         {sf::Keyboard::Key::Num0, EKey::NUMBER0},
//         {sf::Keyboard::Key::Num1, EKey::NUMBER1},
//         {sf::Keyboard::Key::Num2, EKey::NUMBER2},
//         {sf::Keyboard::Key::Num3, EKey::NUMBER3},
//         {sf::Keyboard::Key::Num4, EKey::NUMBER4},
//         {sf::Keyboard::Key::Num5, EKey::NUMBER5},
//         {sf::Keyboard::Key::Num6, EKey::NUMBER6},
//         {sf::Keyboard::Key::Num7, EKey::NUMBER7},
//         {sf::Keyboard::Key::Num8, EKey::NUMBER8},
//         {sf::Keyboard::Key::Num9, EKey::NUMBER9},
//         
//         {sf::Keyboard::Key::Tab, EKey::TAB},
//         {sf::Keyboard::Key::Enter, EKey::ENTER},
//         {sf::Keyboard::Key::Backspace, EKey::BACKSPACE},
//         
//         {sf::Keyboard::Key::Up, EKey::ARROWUP},
//         {sf::Keyboard::Key::Down, EKey::ARROWDOWN},
//         {sf::Keyboard::Key::Right, EKey::ARROWLEFT},
//         {sf::Keyboard::Key::Left, EKey::ARROWRIGHT},
//     };
//     for (auto& Pair : SFMLKeyCodeLinkToAstralKeyCodeRegistry) {
//         AstralKeyCodeLinkToSFMLKeyLinkRegistry.Insert({Pair.second, Pair.first});
//     }
// }
//
// void ASFMLInputManager::HandleInputsEvents(float DeltaTime) {
//     AInputManager::HandleInputsEvents(DeltaTime);
//
//     sf::Event Event;
//     sf::RenderWindow* SFMLWindow = Cast<ASFMLWindow>(GameplayStatics::GetEngine()->GetActiveWindow())->GetPrivateWindow();
//     while (SFMLWindow->pollEvent(Event)) {
//         if (Event.type == sf::Event::Closed) {
//             SFMLWindow->close();
//         }
//         
//         if (IsSFMLEventInputEvent(Event)) {
//             HandleSFMLInputEvent(Event);
//         }
//     }
// }
//
// bool ASFMLInputManager::IsSFMLEventInputEvent(const sf::Event& Event) const {
//     return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased || Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
// }
//
// void ASFMLInputManager::HandleSFMLInputEvent(sf::Event& Event) {
//     if (IsKeyboardInput(Event)) {
//         sf::Keyboard::Key SFMLKey = Event.key.code;
//         if (SupportSFMLKeyboardInput(SFMLKey)) {
//             EKey AstralEngineKey = SFMLKeyCodeToAstralEngineKeyCode(SFMLKey);
//             HandleKeyInput(AstralEngineKey, FInputParams(Event.type == sf::Event::KeyPressed ? EInputState::Pressed : EInputState::Released));
//         }
//     }
//     else if(IsMouseInput(Event)) {
//         //TODO
//     }
// }
//
// EKey ASFMLInputManager::SFMLKeyCodeToAstralEngineKeyCode(sf::Keyboard::Key Key) const{
//     return SFMLKeyCodeLinkToAstralKeyCodeRegistry.Find(Key);
// }
//
// sf::Keyboard::Key ASFMLInputManager::AstralEngineKeyCodeToSFMLKeyCode(EKey Key) const{
//     return AstralKeyCodeLinkToSFMLKeyLinkRegistry.Find(Key);
// }
//
// bool ASFMLInputManager::SupportSFMLKeyboardInput(sf::Keyboard::Key Key) const {
//     return SFMLKeyCodeLinkToAstralKeyCodeRegistry.Contains(Key);
// }
//
// bool ASFMLInputManager::IsKeyboardInput(sf::Event& Event) const {
//     return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased;
// }
//
// bool ASFMLInputManager::IsMouseInput(sf::Event& Event) const {
//     return Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
// }
//
// bool ASFMLInputManager::IsKeyPressed(EKey Key) const {
//     // DECLARE_DELEGATE(FTest, std::string);
//     // auto Lambda = [this](std::string String) {
//     //     auto test = AstralEngineKeyCodeToSFMLKeyCode(EKey::A);
//     // };
//     //
//     // FTest::FromLambda(Lambda);
//     
//     return sf::Keyboard::isKeyPressed(AstralEngineKeyCodeToSFMLKeyCode(Key));
// }
