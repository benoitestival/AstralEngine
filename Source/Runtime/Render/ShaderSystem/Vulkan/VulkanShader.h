#pragma once
#include <vulkan/vulkan_core.h>

#include "../Shader.h"


class FVulkanDevice;
class AVulkanRenderer;
class AShader;

class AVulkanShader : public AShader {
public:

    DECLARE_ASTRAL_ENGINE_CLASS(AVulkanShader, AShader)
    
    AVulkanShader();
    ~AVulkanShader() override;
    
    void InitShader() override;
    virtual void CleanShader() override;

    VkShaderModule GetPrivateShader();
private:

    AVulkanRenderer* GetRenderManager() const;
    FVulkanDevice* GetVkDevice() const;
private:
    AVulkanRenderer* RenderManager = nullptr;
private:
    //AShader* InternShader = nullptr;
    VkShaderModule ShaderModule = VK_NULL_HANDLE;
};
