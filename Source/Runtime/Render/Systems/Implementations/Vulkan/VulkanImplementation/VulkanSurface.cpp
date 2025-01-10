#include "VulkanSurface.h"

#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Engine/Engine.h"
#include "../../../../../Window/Implementations/GLFWWindow.h"

FVulkanSurface::FVulkanSurface() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
    //RenderManager = FVulkanClass::VulkanRenderManager;
}

FVulkanSurface::~FVulkanSurface() {
}

VkResult FVulkanSurface::Init() {
    if (!glfwVulkanSupported()) {
        std::cout << "Vulkan is not supported by GLFW!" << std::endl;
    }
    VkResult Result = glfwCreateWindowSurface(GetRenderManager()->GetVkInstance(), GetWindow()->GetPrivateWindow(), nullptr, &VkSurface); 
    return Result;
}

void FVulkanSurface::Clean() {
    vkDestroySurfaceKHR(GetRenderManager()->GetVkInstance(), VkSurface, nullptr);
}

VkSurfaceKHR FVulkanSurface::GetPrivateSurface() const {
    return VkSurface;
}

AVulkanRenderManager* FVulkanSurface::GetRenderManager() const {
    return RenderManager;
}

AGLFWWindow* FVulkanSurface::GetWindow() {
    return Cast<AGLFWWindow>(GameplayStatics::GetEngine()->GetActiveWindow());
}
