#include "Entity.h"

#include "../ObjectManager.h"
#include "../../Inputs/Components/InputComponent.h"
#include "../../Statics/GameplayStatics.h"
#include "../../Time/TimerManager.h"
#include "../Utils/ObjectCoreUtility.h"


AEntity::AEntity() {
    EntityInputComponent = NewObject<AInputComponent>(AInputComponent::StaticClass(), this);
}

void AEntity::BeginPlay() {
    //GameplayStatics::GetTimerManager()->RegisterTimer(FTimerDelegate::FromLambda([](){}), 2.0f);
}

void AEntity::Tick(float DeltaTime) {
    
}

//
// void AEntity::Serialize(FArchive& Archive) {
//     ABaseObject::Serialize(Archive);
// }
