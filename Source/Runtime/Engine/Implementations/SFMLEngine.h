#pragma once
#include <SFML/Graphics.hpp>

#include "../Engine.h"

class ASFMLEngine : public AEngine {
public:
   DECLARE_ASTRAL_ENGINE_CLASS(ASFMLEngine, AEngine)
   virtual void Start() override;
   void GuardedLoop();
   
   virtual void Tick(float DeltaTime) override;
   virtual void End() override;

   void HandleSFMLInputs();
   bool IsSFMLEventInputType(const sf::Event& Event) const;

   sf::RenderWindow* GetWindow();
private:
   sf::RenderWindow* m_window = nullptr;
};
