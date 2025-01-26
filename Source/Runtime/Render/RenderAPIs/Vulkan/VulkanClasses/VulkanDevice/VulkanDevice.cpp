#include "VulkanDevice.h"

#include "../../VulkanRenderer.h"
#include "../../VulkanHelpers/VulkanLogger.h"
#include "VulkanPhysicalDevice.h"

FVulkanDevice::FVulkanDevice() {
}

FVulkanDevice::~FVulkanDevice() {
}

VkResult FVulkanDevice::Init() {
    VkResult Result = SelectPhysicalDevice();
    if (Result == VK_SUCCESS) {
        FQueueFamilyIndices QueueFamiliesSupported = PhysicalDevice->GetSupportedQueueFamilies();
        TArray<VkDeviceQueueCreateInfo> QueueCreateInfos = {};
        float QueuePriority = 1.0f;

        for (auto QueueFamilyIndice : QueueFamiliesSupported.ToSet()) {
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

        CreateInfo.enabledExtensionCount = PhysicalDevice->GetRequiredDeviceExtensions().Lenght();
        TArray<const char*> EnabledExtensionNames = PhysicalDevice->GetRequiredDeviceExtensions();
        CreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.Data();

        if (GetVKRenderer()->RunInDebug()) {
            CreateInfo.enabledLayerCount = static_cast<uint32_t>(FVulkanLogger::ValidationLayers.Lenght());
            CreateInfo.ppEnabledLayerNames = FVulkanLogger::ValidationLayers.Data();
        }
        else {
            CreateInfo.enabledLayerCount = 0;
        }

        Result = vkCreateDevice(PhysicalDevice->GetPrivateRessource(), &CreateInfo, nullptr, &GetPrivateRessource());
    }
    vkGetDeviceQueue(GetPrivateRessource(), PhysicalDevice->GetSupportedQueueFamilies().GraphicsFamilyIndice, 0, &GraphicsQueue);
    vkGetDeviceQueue(GetPrivateRessource(), PhysicalDevice->GetSupportedQueueFamilies().PresentingFamilyIndice, 0, &PresentingQueue);
    return Result;
}

void FVulkanDevice::Clean() {
    vkDestroyDevice(GetPrivateRessource(), nullptr);
    CleanPhysicalDevice();
}

VkResult FVulkanDevice::SelectPhysicalDevice() {
    PhysicalDevice = new FVulkanPhysicalDevice();
    return PhysicalDevice->Init();
}

void FVulkanDevice::CleanPhysicalDevice() {
    PhysicalDevice->Clean();
    delete PhysicalDevice;
    PhysicalDevice = nullptr;
}

VkQueue FVulkanDevice::GetGraphicsQueue() const {
    return GraphicsQueue;
}

VkQueue FVulkanDevice::GetPresentingQueue() const {
    return PresentingQueue;
}

FVulkanPhysicalDevice* FVulkanDevice::GetVkPhysicalDevice() const {
    return PhysicalDevice;
}
