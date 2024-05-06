#include "Entity.h"

#include "../ObjectManager.h"
#include "../../Inputs/Components/InputComponent.h"


AEntity::AEntity() {
    EntityInputComponent = AObjectManager::Get()->InstanciateNewObject<AInputComponent>(AInputComponent::StaticClass());
}

void AEntity::BeginPlay() {
    
}

void AEntity::Tick(float DeltaTime) {
    
}
