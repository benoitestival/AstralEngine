#include "VulkanDevice.h"

#include "VulkanSurface.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"

FVulkanDevice::FVulkanDevice() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanDevice::~FVulkanDevice() {
}

VkResult FVulkanDevice::Init() {
    VkResult Result = SelectPhysicalDevice();
    if (Result == VK_SUCCESS) {
        Result = CreateLogicalDevice();
    }
    vkGetDeviceQueue(LogicalDevice, GetDeviceSupportedQueueFamilies(PhysicalDevice).GraphicsFamilyIndice, 0, &GraphicsQueue);
    vkGetDeviceQueue(LogicalDevice, GetDeviceSupportedQueueFamilies(PhysicalDevice).PresentingFamilyIndice, 0, &PresentingQueue);
    return Result;
}

void FVulkanDevice::Clean() {
    vkDestroyDevice(LogicalDevice, nullptr);
}

VkPhysicalDevice FVulkanDevice::GetPrivatePhysicalDevice() const {
    return PhysicalDevice;
}

VkDevice FVulkanDevice::GetPrivateLogicalDevice() const {
    return LogicalDevice;
}

VkResult FVulkanDevice::SelectPhysicalDevice() {
    VkResult Result = VK_ERROR_INITIALIZATION_FAILED;
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(GetRenderManager()->GetVkInstance(), &DeviceCount, nullptr);//Only checking for GPU devices
    if (DeviceCount > 0) {
        TArray<VkPhysicalDevice> Devices = TArray<VkPhysicalDevice>(DeviceCount);
        vkEnumeratePhysicalDevices(GetRenderManager()->GetVkInstance(), &DeviceCount, Devices.Data());//Gathering GPU devices

        int HighestScore = -1;
        for (const auto& Device : Devices) {
            int Score = GetDeviceSuitabilityScore(Device);
            if (Score >= HighestScore) {
                PhysicalDevice = Device;
            }
        }
        
        if (PhysicalDevice != VK_NULL_HANDLE) {
            Result = VK_SUCCESS;
        }
    }
    return Result;
}

bool FVulkanDevice::IsDeviceSuitable(VkPhysicalDevice Device) {
    return GetDeviceSupportedQueueFamilies(Device).IsValid();
}

int FVulkanDevice::GetDeviceSuitabilityScore(VkPhysicalDevice Device) {
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


VkResult FVulkanDevice::CreateLogicalDevice() {
    FQueueFamilyIndices QueueFamiliesSupported = GetDeviceSupportedQueueFamilies(PhysicalDevice);
    TArray<VkDeviceQueueCreateInfo> QueueCreateInfos = {};
    float QueuePriority = 1.0f;

    for (auto QueueFamilyIndice : QueueFamiliesSupported.ToArray()) {
        VkDeviceQueueCreateInfo QueueCreateInfo = {};
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.queueFamilyIndex = QueueFamilyIndice;
        QueueCreateInfo.queueCount = 1;

        QueueCreateInfo.pQueuePriorities = &QueuePriority;
        QueueCreateInfos.Add(QueueCreateInfo);
    }

    VkPhysicalDeviceFeatures DeviceFeatures = {};

    VkDeviceCreateInfo CreateInfo = {};
    CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    CreateInfo.pQueueCreateInfos = QueueCreateInfos.Data();
    CreateInfo.queueCreateInfoCount = QueueCreateInfos.Lenght();

    CreateInfo.pEnabledFeatures = &DeviceFeatures;

    CreateInfo.enabledExtensionCount = 0;
    CreateInfo.enabledLayerCount = 0;

    return vkCreateDevice(PhysicalDevice, &CreateInfo, nullptr, &LogicalDevice);
}

FQueueFamilyIndices FVulkanDevice::GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device) {
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
            vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, QUEUE_FAMILY_INDEX, GetRenderManager()->GetVkSurface()->GetPrivateSurface(), &PresentingSupport);
            if (PresentingSupport) {
                FamilyIndices.PresentingFamilyIndice = QUEUE_FAMILY_INDEX;
            }
        }
    }
    
    return FamilyIndices;
}

AVulkanRenderManager* FVulkanDevice::GetRenderManager() const {
    return RenderManager;
}
