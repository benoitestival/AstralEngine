#include "ConfigUtils.h"

#include "../Engine/Engine/Implementations/AstralEngine.h"
#include "../Engine/Inputs/Systems/Implementations/OpenGLInputManager.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"
#include "../Render/Systems/Implementations/OpenGLRenderManager.h"
#include "../Window/Implementations/OpenGLWindow.h"
#include "../Window/Implementations/SFMLWindow.h"


FClass* ConfigUtils::GetEngineClass() {
    return AstralEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return AOpenGLInputManager::StaticClass();
}

FClass* ConfigUtils::GetRenderManagerClass() {
    return AOpenGLRenderManager::StaticClass();
}

FClass* ConfigUtils::GetWindowClass() {
    return AOpenGLWindow::StaticClass();
}
