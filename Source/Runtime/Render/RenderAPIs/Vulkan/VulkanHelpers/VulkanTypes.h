#pragma once

#include <set>
#include <vulkan/vulkan_core.h>
#include "../../../../Utils/Array.h"

#define INVALID_FAMILY_INDICE (-1)

struct FSwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR Capabilities;
    TArray<VkSurfaceFormatKHR> Formats;
    TArray<VkPresentModeKHR> PresentModes;
};

struct FQueueFamilyIndices {
    int GraphicsFamilyIndice = -1;
    int PresentingFamilyIndice = -1;

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
