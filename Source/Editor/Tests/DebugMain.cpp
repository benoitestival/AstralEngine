// ReSharper disable All
#include "DebugMain.h"

#include <iostream>

#include "../../Runtime/Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../../Runtime/Engine/Engine/Engine.h"
#include "../../Runtime/Engine/Inputs/Components/InputComponent.h"
#include "../../Runtime/Engine/Inputs/Objects/InputAction.h"
#include "../../Runtime/Engine/Inputs/Systems/InpuManager.h"
#include "../../Runtime/Engine/Statics/GameplayStatics.h"

int ADebugMain::DebugMain() {
    
    std::cout << "Hello World" << std::endl; 
    // FMatrix4X4 Matrix;
    // FVector2D Vec;
    // Vec * Matrix;
    // Matrix * Vec;
    //////////////////////INPUT TEST////////////////////////
    // AInputAction* InputAction = NewObject<AInputAction>(AInputAction::StaticClass());
    // InputAction->SetDesiredValueType(EInputValueType::EInputAxis2D);
    // InputAction->OnInputTrigger.Bind([](FInputValue InputValue) {
    //     //std::cout << "Frame: " << GameplayStatics::GetEngine()->FrameCount << ", DeltaTime : " << GameplayStatics::GetDeltaTime() << "\n";
    //     //InputValue.InputVector2D.Log();
    //     //std::cout << "///////////////////////////////" << "\n";
    // });
    //
    // AInputComponent* InputComponent = NewObject<AInputComponent>(AInputComponent::StaticClass());
    // InputComponent->RegisterAction(EKey::MOUSEAXISXY, InputAction);
    //
    // GameplayStatics::GetInputManager()->RegisterInputComponent(InputComponent);

    //Depending on if you want to block the engine or allow it to continue after the main enable your return code
    return CONTINUE_CODE;
    //return EXIT_CODE;
}
