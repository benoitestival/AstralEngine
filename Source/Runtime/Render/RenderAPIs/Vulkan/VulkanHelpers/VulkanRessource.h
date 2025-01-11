#pragma once
#include <vulkan/vulkan_core.h>

#include "../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../Utils/TemplateUtils.h"

class AVulkanRenderer;

template<class T>
class TVulkanRessource {
public:
    TVulkanRessource() = default;

    T& GetPrivateRessource(){
        return VulkanRessource;
    }

private:
    T VulkanRessource;
};
