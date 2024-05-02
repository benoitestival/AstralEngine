#include "ASFMLRenderManager.h"

#include "../../../Engine/Implementations/SFMLEngine.h"
#include "../../../Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../Components/SFML/SFMLSpriteComponent.h"

void ASFMLRenderManager::Draw() {
    Super::Draw();
}

void ASFMLRenderManager::Clear() {
    RenderPlans.clear();
    
    sf::RenderWindow* Window = GetRenderWindow();
    Window->clear();
    
    Super::Clear();
}

void ASFMLRenderManager::RegisterSpriteDrawcall(ASFMLSpriteComponent* SpriteComponent, int SpriteZOrder) {
    if (IsSpriteInCameraView(SpriteComponent) && SpriteComponent != nullptr) {
        if (RenderPlans.size() > SpriteZOrder) {
            RenderPlans[SpriteZOrder].RenderPlanSprites.push_back(SpriteComponent);
        }
        else {
            const int PlanSizeDifference = SpriteZOrder - (RenderPlans.size() - 1);
            for (int PLAN_INDEX = 0; PLAN_INDEX < PlanSizeDifference; PLAN_INDEX++) {
                RenderPlans.push_back(FRenderPlan());
            }
            RenderPlans[SpriteZOrder].RenderPlanSprites.push_back(SpriteComponent);
        }
    }
}

bool ASFMLRenderManager::IsSpriteInCameraView(ASFMLSpriteComponent* SpriteComponent) {
    //TODO Add logic here
    return true;
}

sf::RenderWindow* ASFMLRenderManager::GetRenderWindow() {
    return Cast<ASFMLEngine>(GameplayStatics::GetEngine())->GetWindow();
}
