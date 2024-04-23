#pragma once
#include <SFML/Graphics.hpp>
#include "../Engine.h"

class ASFMLEngine : AEngine {
public:
   DECLARE_ASTRAL_ENGINE_CLASS(ASFMLEngine, AEngine)
   //DECLARE_RTTI_NO_MULTI_HERIATGE(ASFMLEngine, AEngine)
   virtual void Start() override;
   virtual void Run() override;
   virtual void End() override;
private:
   sf::RenderWindow* m_window = nullptr;
};
