#include "ConfigUtils.h"

#include "../Engine/Implementations/SFMLEngine.h"
#include "../Inputs/Implementations/SFMLInputManager.h"
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
