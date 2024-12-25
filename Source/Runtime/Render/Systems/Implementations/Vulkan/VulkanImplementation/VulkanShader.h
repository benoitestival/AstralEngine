#pragma once
#include <vulkan/vulkan_core.h>
#include "../../../../../Utils/Path/Path.h"

class FVulkanDevice;
class AVulkanRenderManager;
class AShader;

class FVulkanShader {
public:

    FVulkanShader();
    FVulkanShader(const FPath& ShaderPath);
    ~FVulkanShader();
    
    VkResult Init();
    void Clean();
private:

    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
private:
    AVulkanRenderManager* RenderManager = nullptr;
private:
    FPath ShaderDiskPath;
    AShader* InterShader = nullptr;
    VkShaderModule ShaderModule = VK_NULL_HANDLE;
};
