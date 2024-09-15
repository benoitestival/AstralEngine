#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Window.h"

class ASFMLWindow : public  AWindow{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLWindow, AWindow)

    virtual void Construct() override;
    virtual void Tick(float DeltaTime) override;
    virtual void Close() override;
    
    sf::RenderWindow* GetPrivateWindow() const;
private:
    sf::RenderWindow* Window = nullptr;
};
