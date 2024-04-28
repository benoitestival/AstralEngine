#include "ConfigUtils.h"

#include "../Core/Systems/Inputs/Implementations/SFMLInputManager.h"
#include "../Engine/Implementations/SFMLEngine.h"


FClass* ConfigUtils::GetEngineClass() {
    return ASFMLEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return ASFMLInputManager::StaticClass();
}
