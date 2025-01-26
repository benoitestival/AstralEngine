#pragma once

#include <set>
#include <vulkan/vulkan_core.h>
#include <glm/glm.hpp>
#include "../../../../Maths/Maths.h"
#include "../../../../Utils/Array.h"
#include "../../../../Window/Implementations/GLFWWindow.h"

#define INVALID_FAMILY_INDICE (-1)

class AVulkanRenderer;

struct FVertex {
    FVector2D Position;
    FVector Color;
public:
    static VkVertexInputBindingDescription GetBindingDescription();
    static TArray<VkVertexInputAttributeDescription> GetAttributeDescriptions();
};

struct FSwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR Capabilities;
    TArray<VkSurfaceFormatKHR> Formats;
    TArray<VkPresentModeKHR> PresentModes;
};

struct FQueueFamilyIndices {
    int GraphicsFamilyIndice = -1;
    int PresentingFamilyIndice = -1;
public:
    bool IsValid() const {
        return GraphicsFamilyIndice != INVALID_FAMILY_INDICE && PresentingFamilyIndice != INVALID_FAMILY_INDICE;
    }

    TArray<int> ToArray() {
        return {GraphicsFamilyIndice, PresentingFamilyIndice};
    }
    std::set<int> ToSet() {
        return {GraphicsFamilyIndice, PresentingFamilyIndice};
    }
    TArray<uint32_t> ToUnsignedArray() {
        return {(uint32_t)GraphicsFamilyIndice, (uint32_t)PresentingFamilyIndice};
    }
};


class VulkanTypes {
public:
};
