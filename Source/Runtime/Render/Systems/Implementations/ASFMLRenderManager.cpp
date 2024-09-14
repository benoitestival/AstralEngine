#include "ASFMLRenderManager.h"

#include "../../../Engine/Engine/Engine.h"
#include "../../../Engine/Statics/GameplayStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../../Window/Implementations/SFMLWindow.h"
#include "../../Components/SFML/SFMLSpriteComponent.h"

void ASFMLRenderManager::Draw() {
    Super::Draw();
}

void ASFMLRenderManager::Clear() {
    RenderPlans.Clear();
    
    sf::RenderWindow* Window = GetRenderWindow();
    Window->clear();
    
    Super::Clear();
}

void ASFMLRenderManager::RegisterSpriteDrawcall(ASFMLSpriteComponent* SpriteComponent, int SpriteZOrder) {
    if (IsSpriteInCameraView(SpriteComponent) && SpriteComponent != nullptr) {
        if (RenderPlans.Lenght() > SpriteZOrder) {
            RenderPlans[SpriteZOrder].RenderPlanSprites.Add(SpriteComponent);
        }
        else {
            const int PlanSizeDifference = SpriteZOrder - (RenderPlans.Lenght() - 1);
            for (int PLAN_INDEX = 0; PLAN_INDEX < PlanSizeDifference; PLAN_INDEX++) {
                RenderPlans.Add(FRenderPlan());
            }
            RenderPlans[SpriteZOrder].RenderPlanSprites.Add(SpriteComponent);
        }
    }
    
}

bool ASFMLRenderManager::IsSpriteInCameraView(ASFMLSpriteComponent* SpriteComponent) {
    //TODO Add logic here
    return true;
}

sf::RenderWindow* ASFMLRenderManager::GetRenderWindow() {
    return Cast<ASFMLWindow>(GameplayStatics::GetEngine()->GetActiveWindow())->GetPrivateWindow();
}
