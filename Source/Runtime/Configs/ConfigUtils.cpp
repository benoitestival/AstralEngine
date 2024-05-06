#include "ConfigUtils.h"

#include "../Engine/Engine/Implementations/SFMLEngine.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"


FClass* ConfigUtils::GetEngineClass() {
    return ASFMLEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return ASFMLInputManager::StaticClass();
}

FClass* ConfigUtils::GetRenderManagerClass() {
    return ASFMLRenderManager::StaticClass();
}
