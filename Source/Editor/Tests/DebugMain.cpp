// ReSharper disable All
#include "DebugMain.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <glm/gtx/transform.hpp>

#include "../../Runtime/Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../../Runtime/Engine/Engine/Engine.h"
#include "../../Runtime/Engine/Inputs/Components/InputComponent.h"
#include "../../Runtime/Engine/Inputs/Objects/InputAction.h"
#include "../../Runtime/Engine/Inputs/Systems/InpuManager.h"
#include "../../Runtime/Engine/Statics/GameplayStatics.h"
#include "../../Runtime/Serialization/Archive/Implementations/JsonArchive.h"

int ADebugMain::DebugMain() {
    
    return CONTINUE_CODE;
    //return EXIT_CODE;
}
