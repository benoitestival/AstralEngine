#include "ASFMLRenderManager.h"

#include "../../../Engine/Implementations/SFMLEngine.h"
#include "../../../Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"

void ASFMLRenderManager::Draw() {
    Super::Draw();
}

void ASFMLRenderManager::Clear() {
    RenderPlans.clear();
    
    sf::RenderWindow* Window = GetRenderWindow();
    Window->clear();
    
    Super::Clear();
}

void ASFMLRenderManager::RegisterSpriteDrawcall(sf::Sprite* Sprite, const FTransform& SpriteTransform, int SpriteZOrder) {
    if (IsSpriteInCameraView(Sprite, SpriteTransform) && Sprite != nullptr) {
        if (RenderPlans.size() > SpriteZOrder) {
            RenderPlans[SpriteZOrder].RenderPlanSprites.push_back(Sprite);
        }
        else {
            const int PlanSizeDifference = SpriteZOrder - (RenderPlans.size() - 1);
            for (int PLAN_INDEX = 0; PLAN_INDEX < PlanSizeDifference; PLAN_INDEX++) {
                RenderPlans.push_back(FRenderPlan());
            }
            RenderPlans[SpriteZOrder].RenderPlanSprites.push_back(Sprite);
        }
    }
}

bool ASFMLRenderManager::IsSpriteInCameraView(sf::Sprite* Sprite, const FTransform& SpriteTransform) {
    //TODO Add logic here
    return true;
}

sf::RenderWindow* ASFMLRenderManager::GetRenderWindow() {
    return Cast<ASFMLEngine>(GameplayStatics::GetEngine())->GetWindow();
}
