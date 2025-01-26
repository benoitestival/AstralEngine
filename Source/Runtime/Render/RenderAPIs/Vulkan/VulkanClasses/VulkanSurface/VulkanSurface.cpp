#include "VulkanSurface.h"


#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "../../../../../Engine/Engine/Engine.h"
#include "../../VulkanRenderer.h"


FVulkanSurface::FVulkanSurface(){
}

FVulkanSurface::~FVulkanSurface() {
}

VkResult FVulkanSurface::Init() {
    if (!glfwVulkanSupported()) {
        std::cout << "Vulkan is not supported by GLFW!" << std::endl;
    }
    //VkResult Result = ; 
    //VkResult Result = glfwCreateWindowSurface(GetVKRenderer()->GetVkInstance(), VulkanTypes::Window, nullptr, &GetPrivateRessource()); 
    return glfwCreateWindowSurface(GetVKRenderer()->GetVkInstance(), GetWindow()->GetPrivateWindow(), nullptr, &GetPrivateRessource());
}

void FVulkanSurface::Clean() {
    vkDestroySurfaceKHR(GetVKRenderer()->GetVkInstance(), GetPrivateRessource(), nullptr);
}

AGLFWWindow* FVulkanSurface::GetWindow() {
    return Cast<AGLFWWindow>(GameplayStatics::GetEngine()->GetActiveWindow());
}
