#include "SFMLInputManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../../Window/Implementations/SFMLWindow.h"
#include "../../../Engine/Engine.h"
#include "../../../Statics/GameplayStatics.h"

void ASFMLInputManager::Init() {
    Super::Init();
    SFMLKeyCodeLinkToAstralKeyCodeRegistry = {
        std::make_pair(sf::Keyboard::Key::A, EKey::A),
        std::make_pair(sf::Keyboard::Key::B, EKey::B),
        std::make_pair(sf::Keyboard::Key::C, EKey::C),
        std::make_pair(sf::Keyboard::Key::D, EKey::D),
        std::make_pair(sf::Keyboard::Key::E, EKey::E),
        std::make_pair(sf::Keyboard::Key::F, EKey::F),
        std::make_pair(sf::Keyboard::Key::G, EKey::G),
        std::make_pair(sf::Keyboard::Key::H, EKey::H),
        std::make_pair(sf::Keyboard::Key::I, EKey::I),
        std::make_pair(sf::Keyboard::Key::J, EKey::J),
        std::make_pair(sf::Keyboard::Key::K, EKey::K),
        std::make_pair(sf::Keyboard::Key::L, EKey::L),
        std::make_pair(sf::Keyboard::Key::M, EKey::M),
        std::make_pair(sf::Keyboard::Key::N, EKey::N),
        std::make_pair(sf::Keyboard::Key::O, EKey::O),
        std::make_pair(sf::Keyboard::Key::P, EKey::P),
        std::make_pair(sf::Keyboard::Key::Q, EKey::Q),
        std::make_pair(sf::Keyboard::Key::R, EKey::R),
        std::make_pair(sf::Keyboard::Key::S, EKey::S),
        std::make_pair(sf::Keyboard::Key::T, EKey::T),
        std::make_pair(sf::Keyboard::Key::U, EKey::U),
        std::make_pair(sf::Keyboard::Key::V, EKey::V),
        std::make_pair(sf::Keyboard::Key::W, EKey::W),
        std::make_pair(sf::Keyboard::Key::X, EKey::X),
        std::make_pair(sf::Keyboard::Key::Y, EKey::Y),
        std::make_pair(sf::Keyboard::Key::Z, EKey::Z),
        
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
        AstralKeyCodeLinkToSFMLKeyLinkRegistry.Insert(std::make_pair(Pair.second, Pair.first));
    }
}

void ASFMLInputManager::HandleInputsEvents() {
    AInputManager::HandleInputsEvents();

    sf::Event Event;
    sf::RenderWindow* SFMLWindow = Cast<ASFMLWindow>(GameplayStatics::GetEngine()->GetActiveWindow())->GetPrivateWindow();
    while (SFMLWindow->pollEvent(Event)) {
        if (Event.type == sf::Event::Closed) {
            SFMLWindow->close();
        }
        
        if (IsSFMLEventInputEvent(Event)) {
            HandleSFMLInputEvent(Event);
        }
    }
}

bool ASFMLInputManager::IsSFMLEventInputEvent(const sf::Event& Event) const {
    return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased || Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
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
    return SFMLKeyCodeLinkToAstralKeyCodeRegistry.Find(Key);
}

sf::Keyboard::Key ASFMLInputManager::AstralEngineKeyCodeToSFMLKeyCode(EKey Key) const{
    return AstralKeyCodeLinkToSFMLKeyLinkRegistry.Find(Key);
}

bool ASFMLInputManager::SupportSFMLKeyboardInput(sf::Keyboard::Key Key) const {
    return SFMLKeyCodeLinkToAstralKeyCodeRegistry.Contains(Key);
}

bool ASFMLInputManager::IsKeyboardInput(sf::Event& Event) const {
    return Event.type == sf::Event::KeyPressed || Event.type == sf::Event::KeyReleased;
}

bool ASFMLInputManager::IsMouseInput(sf::Event& Event) const {
    return Event.type == sf::Event::MouseMoved || Event.type == sf::Event::MouseButtonPressed ||Event.type == sf::Event::MouseButtonReleased || Event.type == sf::Event::MouseWheelMoved || Event.type == sf::Event::MouseWheelScrolled;
}

bool ASFMLInputManager::IsKeyPressed(EKey Key) const {
    // DECLARE_DELEGATE(FTest, std::string);
    // auto Lambda = [this](std::string String) {
    //     auto test = AstralEngineKeyCodeToSFMLKeyCode(EKey::A);
    // };
    //
    // FTest::FromLambda(Lambda);
    
    return sf::Keyboard::isKeyPressed(AstralEngineKeyCodeToSFMLKeyCode(Key));
}
