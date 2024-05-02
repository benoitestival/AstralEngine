#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../RenderManager.h"
#include "../../../Maths/Transform.h"
#include "../../../Utils/Array.h"


class ASFMLSpriteComponent;

struct FRenderPlan {
    TArray<ASFMLSpriteComponent*> RenderPlanSprites;
};

class ASFMLRenderManager : public ARenderManager{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ASFMLRenderManager, ARenderManager)

    virtual void Draw() override;
    virtual void Clear() override;
    
    void RegisterSpriteDrawcall(ASFMLSpriteComponent* SpriteComponent, int SpriteZOrder);
    bool IsSpriteInCameraView(ASFMLSpriteComponent* SpriteComponent);
private:
    sf::RenderWindow* GetRenderWindow();
    
private:
    TArray<FRenderPlan> RenderPlans;
};
