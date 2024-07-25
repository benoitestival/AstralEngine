#include "ConfigUtils.h"

#include "../../Editor/Tests/TestEngine.h"
#include "../Engine/Engine/Implementations/SFMLEngine.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"


FClass* ConfigUtils::GetEngineClass() {
    return ATestEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return ASFMLInputManager::StaticClass();
}

FClass* ConfigUtils::GetRenderManagerClass() {
    return ASFMLRenderManager::StaticClass();
}
