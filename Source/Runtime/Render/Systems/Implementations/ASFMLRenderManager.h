#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../RenderManager.h"
#include "../../../Maths/Transform.h"
#include "../../../Utils/Array.h"


struct FRenderPlan {
    TArray<sf::Sprite*> RenderPlanSprites;
};

class ASFMLRenderManager : public ARenderManager{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLRenderManager, ARenderManager)

    virtual void Draw() override;
    virtual void Clear() override;
    
    void RegisterSpriteDrawcall(sf::Sprite* Sprite, const FTransform& SpriteTransform, int SpriteZOrder);
    bool IsSpriteInCameraView(sf::Sprite* Sprite, const FTransform& SpriteTransform);
private:
    sf::RenderWindow* GetRenderWindow();
    
private:
    TArray<FRenderPlan> RenderPlans;
};
