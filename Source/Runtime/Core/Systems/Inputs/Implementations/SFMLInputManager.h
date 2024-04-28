#pragma once
#include <SFML/Window/Event.hpp>

#include "../InpuManager.h"

class ASFMLInputManager : public  AInpuManager{
public:
    DECLARE_RTTI(ASFMLInputManager)

public:
    void HandleSFMLInputEvent(sf::Event& Event);
};
