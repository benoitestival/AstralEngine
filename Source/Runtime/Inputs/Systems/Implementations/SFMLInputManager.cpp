#include "SFMLInputManager.h"

void ASFMLInputManager::Init() {
    Super::Init();
    SFMLKeyCodeLinkToAstralKeyCodeRegistry = {
        std::make_pair(sf::Keyboard::Key::A, EKey::A),
        std::make_pair(sf::Keyboard::Key::B, EKey::A),
        std::make_pair(sf::Keyboard::Key::C, EKey::A),
        std::make_pair(sf::Keyboard::Key::D, EKey::A),
        std::make_pair(sf::Keyboard::Key::E, EKey::A),
        std::make_pair(sf::Keyboard::Key::F, EKey::A),
        std::make_pair(sf::Keyboard::Key::G, EKey::A),
        std::make_pair(sf::Keyboard::Key::H, EKey::A),
        std::make_pair(sf::Keyboard::Key::I, EKey::A),
        std::make_pair(sf::Keyboard::Key::J, EKey::A),
        std::make_pair(sf::Keyboard::Key::K, EKey::A),
        std::make_pair(sf::Keyboard::Key::L, EKey::A),
        std::make_pair(sf::Keyboard::Key::M, EKey::A),
        std::make_pair(sf::Keyboard::Key::N, EKey::A),
        std::make_pair(sf::Keyboard::Key::O, EKey::A),
        std::make_pair(sf::Keyboard::Key::P, EKey::A),
        std::make_pair(sf::Keyboard::Key::Q, EKey::A),
        std::make_pair(sf::Keyboard::Key::R, EKey::A),
        std::make_pair(sf::Keyboard::Key::S, EKey::A),
        std::make_pair(sf::Keyboard::Key::T, EKey::A),
        std::make_pair(sf::Keyboard::Key::U, EKey::A),
        std::make_pair(sf::Keyboard::Key::V, EKey::A),
        std::make_pair(sf::Keyboard::Key::W, EKey::A),
        std::make_pair(sf::Keyboard::Key::X, EKey::A),
        std::make_pair(sf::Keyboard::Key::Y, EKey::A),
        std::make_pair(sf::Keyboard::Key::Z, EKey::A),
        std::make_pair(sf::Keyboard::Key::Space, EKey::SPACE),
        std::make_pair(sf::Keyboard::Key::Escape, EKey::ESCAPE),
        std::make_pair(sf::Keyboard::Key::LControl, EKey::LCTRL),
        std::make_pair(sf::Keyboard::Key::RControl, EKey::RCTRL),
        std::make_pair(sf::Keyboard::Key::LShift, EKey::LSHIFT),
        std::make_pair(sf::Keyboard::Key::RShift, EKey::RSHIFT),
        std::make_pair(sf::Keyboard::Key::LAlt, EKey::LALT),
        std::make_pair(sf::Keyboard::Key::RAlt, EKey::RALT),
        std::make_pair(sf::Keyboard::Key::Num0, EKey::NUMBER0),
        std::make_pair(sf::Keyboard::Key::Num1, EKey::NUMBER1),
        std::make_pair(sf::Keyboard::Key::Num2, EKey::NUMBER2),
        std::make_pair(sf::Keyboard::Key::Num3, EKey::NUMBER3),
        std::make_pair(sf::Keyboard::Key::Num4, EKey::NUMBER4),
        std::make_pair(sf::Keyboard::Key::Num5, EKey::NUMBER5),
        std::make_pair(sf::Keyboard::Key::Num6, EKey::NUMBER6),
        std::make_pair(sf::Keyboard::Key::Num7, EKey::NUMBER7),
        std::make_pair(sf::Keyboard::Key::Num8, EKey::NUMBER8),
        std::make_pair(sf::Keyboard::Key::Num9, EKey::NUMBER9),
        std::make_pair(sf::Keyboard::Key::Tab, EKey::TAB),
        std::make_pair(sf::Keyboard::Key::Enter, EKey::ENTER),
        std::make_pair(sf::Keyboard::Key::Backspace, EKey::BACKSPACE),
        std::make_pair(sf::Keyboard::Key::Up, EKey::ARROWUP),
        std::make_pair(sf::Keyboard::Key::Down, EKey::ARROWDOWN),
        std::make_pair(sf::Keyboard::Key::Right, EKey::ARROWLEFT),
        std::make_pair(sf::Keyboard::Key::Left, EKey::ARROWRIGHT),
    };
    for (auto& Pair : SFMLKeyCodeLinkToAstralKeyCodeRegistry) {
        AstralKeyCodeLinkToSFMLKeyLinkRegistry.insert(std::make_pair(Pair.second, Pair.first));
    }
}

void ASFMLInputManager::HandleSFMLInputEvent(sf::Event& Event) {
    if (IsKeyboardInput(Event)) {
        sf::Keyboard::Key SFMLKey = Event.key.code;
        if (SupportSFMLKeyboardInput(SFMLKey)) {
            EKey AstralEngineKey = SFMLKeyCodeToAstralEngineKeyCode(SFMLKey);
            HandleKeyInput(AstralEngineKey, Event.type == sf::Event::KeyPressed ? EInputState::Pressed : EInputState::Released);
        }
    }
    else if(IsMouseInput(Event)) {
        
    }
}

EKey ASFMLInputManager::SFMLKeyCodeToAstralEngineKeyCode(sf::Keyboard::Key Key) const{
    return SFMLKeyCodeLinkToAstralKeyCodeRegistry.at(Key);
}

sf::Keyboard::Key ASFMLInputManager::AstralEngineKeyCodeToSFMLKeyCode(EKey Key) const{
    return AstralKeyCodeLinkToSFMLKeyLinkRegistry.at(Key);
}

bool ASFMLInputManager::SupportSFMLKeyboardInput(sf::Keyboard::Key Key) const {
    return SFMLKeyCodeLinkToAstralKeyCodeRegistry.contains(Key);
}

bool ASFMLInputManager::IsKeyboardInput(sf::Event& Event) const {
    return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased;
}

bool ASFMLInputManager::IsMouseInput(sf::Event& Event) const {
    return Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
}

bool ASFMLInputManager::IsKeyPressed(EKey Key) const {
    return sf::Keyboard::isKeyPressed(AstralEngineKeyCodeToSFMLKeyCode(Key));
}
