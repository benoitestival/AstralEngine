#include "VulkanPhysicalDevice.h"

#include "../../VulkanRenderer.h"
#include "../VulkanSurface/VulkanSurface.h"


FVulkanPhysicalDevice::FVulkanPhysicalDevice() {
}

FVulkanPhysicalDevice::~FVulkanPhysicalDevice() {
}

VkResult FVulkanPhysicalDevice::Init() {

    VkResult Result = VK_ERROR_INITIALIZATION_FAILED;
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(GetVKRenderer()->GetVkInstance(), &DeviceCount, nullptr);//Only checking for GPU devices
    if (DeviceCount > 0) {
        TArray<VkPhysicalDevice> Devices = TArray<VkPhysicalDevice>(DeviceCount);
        vkEnumeratePhysicalDevices(GetVKRenderer()->GetVkInstance(), &DeviceCount, Devices.Data());//Gathering GPU devices

        int HighestScore = -1;
        for (const auto& Device : Devices) {
            int Score = GetDeviceSuitabilityScore(Device);
            if (Score >= HighestScore) {
                GetPrivateRessource() = Device;
            }
        }
        
        if (GetPrivateRessource() != VK_NULL_HANDLE) {
            Result = VK_SUCCESS;
        }
    }
    return Result;
}

void FVulkanPhysicalDevice::Clean() {
    FVulkanObject::Clean();
}

FQueueFamilyIndices FVulkanPhysicalDevice::GetSupportedQueueFamilies() {
    return GetDeviceSupportedQueueFamilies(GetPrivateRessource());
}

FQueueFamilyIndices FVulkanPhysicalDevice::GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device) {
    FQueueFamilyIndices FamilyIndices;

    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);//Only checking for Families
    if (QueueFamilyCount > 0) {
        TArray<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.Data());//Gathering Families

        for (int QUEUE_FAMILY_INDEX = 0; QUEUE_FAMILY_INDEX < QueueFamilies.Lenght(); QUEUE_FAMILY_INDEX++) {
            //Check for the graphic family who is obligatory
            if (QueueFamilies[QUEUE_FAMILY_INDEX].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                FamilyIndices.GraphicsFamilyIndice = QUEUE_FAMILY_INDEX;
            }

            //Check for the presenting family
            VkBool32 PresentingSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(GetPrivateRessource(), QUEUE_FAMILY_INDEX, GetVkSurface()->GetPrivateRessource(), &PresentingSupport);
            if (PresentingSupport) {
                FamilyIndices.PresentingFamilyIndice = QUEUE_FAMILY_INDEX;
            }

            if (FamilyIndices.IsValid()) {
                break;
            }
        }
    }
    
    return FamilyIndices;
}

FSwapChainSupportDetails FVulkanPhysicalDevice::QuerySwapChainSupportDetails() {
    return QuerySwapChainSupportForDevice(GetPrivateRessource());
}


FSwapChainSupportDetails FVulkanPhysicalDevice::QuerySwapChainSupportForDevice(VkPhysicalDevice Device) {
    FSwapChainSupportDetails SwapChainSupportDetails = {};

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Device, GetVkSurface()->GetPrivateRessource(), &SwapChainSupportDetails.Capabilities);
    
    uint32_t FormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(Device, GetVkSurface()->GetPrivateRessource(), &FormatCount, nullptr);
    if (FormatCount != 0) {
        SwapChainSupportDetails.Formats.Resize(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(Device, GetVkSurface()->GetPrivateRessource(), &FormatCount, SwapChainSupportDetails.Formats.Data());
    }

    uint32_t PresentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(Device, GetVkSurface()->GetPrivateRessource(), &PresentModeCount, nullptr);

    if (PresentModeCount != 0) {
        SwapChainSupportDetails.PresentModes.Resize(PresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(Device, GetVkSurface()->GetPrivateRessource(), &PresentModeCount, SwapChainSupportDetails.PresentModes.Data());
    }
    
    return SwapChainSupportDetails;
}

bool FVulkanPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice Device) {
    bool RequiredQueueFamiliesAreValid = GetDeviceSupportedQueueFamilies(Device).IsValid();

    bool SupportRequiredExtensions = CheckDeviceSupportRequiredExtensions(Device);

    bool SwapChainAdequate = false;
    if (SupportRequiredExtensions) {
        FSwapChainSupportDetails SwapChainSupport = QuerySwapChainSupportForDevice(Device);
        SwapChainAdequate = SwapChainSupport.Formats.Lenght() != 0 && SwapChainSupport.PresentModes.Lenght() != 0;
    }
    return RequiredQueueFamiliesAreValid && SupportRequiredExtensions && SwapChainAdequate;
}



bool FVulkanPhysicalDevice::CheckDeviceSupportRequiredExtensions(VkPhysicalDevice Device) {
    uint32_t ExtensionCount;
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> AvailableExtensions(ExtensionCount);
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, AvailableExtensions.data());

    TArray<std::string> RequiredExtensions = GetRequiredDeviceExtensionsAsString();
    for (const auto& Extension : AvailableExtensions) {
        RequiredExtensions.Remove(Extension.extensionName);
    }

    return RequiredExtensions.Lenght() == 0;
}

int FVulkanPhysicalDevice::GetDeviceSuitabilityScore(VkPhysicalDevice Device) {
    int DeviceScore = 0;
    
    VkPhysicalDeviceProperties DeviceProperties = {};
    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);

    VkPhysicalDeviceFeatures DeviceFeatures = {};
    vkGetPhysicalDeviceFeatures(Device, &DeviceFeatures);

    //Check if we are not on an integrated GPU
    if (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        DeviceScore = DeviceScore + 1000;
    }

    //Check for higher Texture resolution
    DeviceScore = DeviceScore + DeviceProperties.limits.maxImageDimension2D;

    if (!DeviceFeatures.geometryShader) {
        DeviceScore = -1;   
    }
    
    return DeviceScore;
}

TArray<const char*> FVulkanPhysicalDevice::GetRequiredDeviceExtensions() {
    return {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
}

TArray<std::string> FVulkanPhysicalDevice::GetRequiredDeviceExtensionsAsString() {
    TArray<std::string> ExtensionsName = {};
    for (auto& Elem : GetRequiredDeviceExtensions()) {
        ExtensionsName.Add(Elem);
    }
    return ExtensionsName;
}

FVulkanSurface* FVulkanPhysicalDevice::GetVkSurface() const {
    return GetVKRenderer()->GetVkSurface();
}

