#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine.h"

class ASFMLEngine : public AEngine {
public:
   DECLARE_ASTRAL_ENGINE_CLASS(ASFMLEngine, AEngine)
   virtual void Start() override;
   virtual void Run() override;
   virtual void End() override;

   void HandleSFMLEvents();
private:
   sf::RenderWindow* m_window = nullptr;
};
