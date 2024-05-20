#include "Component.h"

AComponent::AComponent() {
    ParentEntity = nullptr;
}

void AComponent::Init(AEntity* Owner) {
    ParentEntity = Owner;
}

void AComponent::Tick(float DeltaTime) {
    
}
