#pragma once
#include <vulkan/vulkan_core.h>

#include "../Shader.h"


class FVulkanDevice;
class AVulkanRenderManager;
class AShader;

class AVulkanShader : public AShader {
public:

    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanShader, AShader)
    
    AVulkanShader();
    ~AVulkanShader() override;
    
    VkResult Init();
    virtual void CleanShader() override;

    VkShaderModule GetPrivateShader();
private:

    AVulkanRenderManager* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
private:
    AVulkanRenderManager* RenderManager = nullptr;
private:
    //AShader* InternShader = nullptr;
    VkShaderModule ShaderModule = VK_NULL_HANDLE;
};
