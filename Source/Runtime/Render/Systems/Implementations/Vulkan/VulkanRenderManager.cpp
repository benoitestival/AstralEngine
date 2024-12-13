#include "VulkanRenderManager.h"

#include <optional>
#include <GLFW/glfw3.h>

void AVulkanRenderManager::Init() {
    ARenderManager::Init();

    if (CreateInstance() == VK_SUCCESS) {
        if (SelectPhysicalDevice() == VK_SUCCESS) {
            CreateLogicalDevice();
            
            vkGetDeviceQueue(LogicalDevice, GetDeviceSupportedQueueFamilies(PhysicalDevice).GraphicsFamilyIndice, 0, &GraphicsQueue);
        }
    }
    else {
        //TODO throw an exception
    }
    
}

void AVulkanRenderManager::DeInit() {
    vkDestroyInstance(VulkanInstance, nullptr);
    vkDestroyDevice(LogicalDevice, nullptr);
    ARenderManager::DeInit();
}

VkResult AVulkanRenderManager::CreateInstance() {
    VkApplicationInfo VkAppInfo = {};
    VkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    VkAppInfo.pApplicationName = "Astral Engine";
    VkAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    VkAppInfo.pEngineName = "Astral Engine";
    VkAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    VkAppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo VkCreateInfo = {};
    VkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkCreateInfo.pApplicationInfo = &VkAppInfo;

    uint32_t GlfwExtensionCount;
    const char** GlfwExtensionsName;
    GlfwExtensionsName = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);
    
    VkCreateInfo.enabledExtensionCount = GlfwExtensionCount;
    VkCreateInfo.ppEnabledExtensionNames = GlfwExtensionsName;

    VkCreateInfo.enabledLayerCount = 0;

    return vkCreateInstance(&VkCreateInfo, nullptr, &VulkanInstance);
}

VkResult AVulkanRenderManager::SelectPhysicalDevice() {
    VkResult Result = VK_ERROR_INITIALIZATION_FAILED;
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(VulkanInstance, &DeviceCount, nullptr);//Only checking for GPU devices
    if (DeviceCount > 0) {
        TArray<VkPhysicalDevice> Devices = TArray<VkPhysicalDevice>(DeviceCount);
        vkEnumeratePhysicalDevices(VulkanInstance, &DeviceCount, Devices.Data());//Gathering GPU devices

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

bool AVulkanRenderManager::IsDeviceSuitable(VkPhysicalDevice Device) {
    return GetDeviceSupportedQueueFamilies(Device).IsValid();
}

int AVulkanRenderManager::GetDeviceSuitabilityScore(VkPhysicalDevice Device) {
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


VkResult AVulkanRenderManager::CreateLogicalDevice() {
    VkDeviceQueueCreateInfo QueueCreateInfo = {};
    QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    QueueCreateInfo.queueFamilyIndex = GetDeviceSupportedQueueFamilies(PhysicalDevice).GraphicsFamilyIndice;
    QueueCreateInfo.queueCount = 1;    

    float QueuePriority = 1.0f;
    QueueCreateInfo.pQueuePriorities = &QueuePriority;

    VkPhysicalDeviceFeatures DeviceFeatures = {};

    VkDeviceCreateInfo CreateInfo = {};
    CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    CreateInfo.pQueueCreateInfos = &QueueCreateInfo;
    CreateInfo.queueCreateInfoCount = 1;

    CreateInfo.pEnabledFeatures = &DeviceFeatures;

    CreateInfo.enabledExtensionCount = 0;
    CreateInfo.enabledLayerCount = 0;

    return vkCreateDevice(PhysicalDevice, &CreateInfo, nullptr, &LogicalDevice);
}


FQueueFamilyIndices AVulkanRenderManager::GetDeviceSupportedQueueFamilies(VkPhysicalDevice Device) {
    FQueueFamilyIndices FamilyIndices;

    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);//Only checking for Families
    if (QueueFamilyCount > 0) {
        TArray<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.Data());//Gathering Families

        for (int QUEUE_FAMILY_INDEX = 0; QUEUE_FAMILY_INDEX < QueueFamilies.Lenght(); QUEUE_FAMILY_INDEX++) {
            if (QueueFamilies[QUEUE_FAMILY_INDEX].queueFlags & VK_QUEUE_GRAPHICS_BIT) {//Check for the graphic family who is obligatory
                FamilyIndices.GraphicsFamilyIndice = QUEUE_FAMILY_INDEX;
            }
        }
    }
    
    return FamilyIndices;
}
