#pragma once
#include <SFML/Window/Event.hpp>

#include "../InpuManager.h"

class ASFMLInputManager : public  AInputManager{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLInputManager, AInputManager)

public:
    virtual void Init() override;
    
    void HandleSFMLInputEvent(sf::Event& Event);
    EKey SFMLKeyCodeToAstralEngineKeyCode(sf::Keyboard::Key Key) const;
    sf::Keyboard::Key AstralEngineKeyCodeToSFMLKeyCode(EKey Key) const;

    bool SupportSFMLKeyboardInput(sf::Keyboard::Key Key) const;
    
    bool IsKeyboardInput(sf::Event& Event) const;
    bool IsMouseInput(sf::Event& Event) const;

    virtual bool IsKeyPressed(EKey Key) const override;
private:

    std::unordered_map<sf::Keyboard::Key, EKey> SFMLKeyCodeLinkToAstralKeyCodeRegistry;
    std::unordered_map<EKey, sf::Keyboard::Key> AstralKeyCodeLinkToSFMLKeyLinkRegistry;
};
