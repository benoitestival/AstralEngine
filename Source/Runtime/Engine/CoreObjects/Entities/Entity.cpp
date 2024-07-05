#include "Entity.h"

#include "../ObjectManager.h"
#include "../../Inputs/Components/InputComponent.h"
#include "../../Statics/GameplayStatics.h"
#include "../../Time/TimerManager.h"


AEntity::AEntity() {
    EntityInputComponent = AObjectManager::Get()->InstanciateNewObject<AInputComponent>(AInputComponent::StaticClass());
}

void AEntity::BeginPlay() {
    //GameplayStatics::GetTimerManager()->RegisterTimer(FTimerDelegate::FromLambda([](){}), 2.0f);
}

void AEntity::Tick(float DeltaTime) {
    
}

void AEntity::Serialize(FArchive& Archive) {
    ABaseObject::Serialize(Archive);
}
