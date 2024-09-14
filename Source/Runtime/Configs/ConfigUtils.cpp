#include "ConfigUtils.h"

#include "../../Editor/Tests/TestEngine.h"
#include "../Engine/Engine/Implementations/AstralEngine.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"
#include "../Window/Implementations/SFMLWindow.h"


FClass* ConfigUtils::GetEngineClass() {
    return AstralEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return ASFMLInputManager::StaticClass();
}

FClass* ConfigUtils::GetRenderManagerClass() {
    return ASFMLRenderManager::StaticClass();
}

FClass* ConfigUtils::GetWindowClass() {
    return ASFMLWindow::StaticClass();
}
