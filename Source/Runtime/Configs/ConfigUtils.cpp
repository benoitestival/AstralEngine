#include "ConfigUtils.h"

#include "../Engine/Engine/Implementations/AstralEngine.h"
#include "../Engine/Inputs/Systems/Implementations/GLFWInputManager.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/RenderAPIs/Implementations/ASFMLRenderManager.h"
#include "../Render/RenderAPIs/Implementations/OpenGLRenderManager.h"
#include "../Render/RenderAPIs/Implementations/Vulkan/VulkanRenderManager.h"
#include "../Window/Implementations/GLFWWindow.h"
#include "../Window/Implementations/SFMLWindow.h"


FClass* ConfigUtils::GetEngineClass() {
    return AstralEngine::StaticClass();
}

FClass* ConfigUtils::GetInputManagerClass() {
    return AOpenGLInputManager::StaticClass();
}

FClass* ConfigUtils::GetRenderManagerClass() {
    return AVulkanRenderManager::StaticClass();
}

FClass* ConfigUtils::GetWindowClass() {
    return AGLFWWindow::StaticClass();
}
