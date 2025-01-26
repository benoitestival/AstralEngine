#pragma once
#include "../../VulkanObject.h"
#include "../../VulkanHelpers/VulkanBufferRessource.h"

class FVulkanCommandBuffer;
class FVulkanPhysicalDevice;
class FVulkanDevice;

class FVulkanBaseBuffer : public FVulkanObject, public TVulkanBufferRessource<VkBuffer, VkDeviceMemory>{
public:
    FVulkanBaseBuffer();
    ~FVulkanBaseBuffer() override;

    virtual VkResult Init() override;
    virtual void Clean() override;
protected:
    VkResult CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory);
    VkResult CopyBuffer(VkBuffer SrcBuffer, VkBuffer DstBuffer, VkDeviceSize size);
private:
    uint32_t GetMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties);
    VkCommandPool CreateTransientVkCommandPool();
protected:
    FVulkanDevice* GetVkDevice();
    FVulkanPhysicalDevice* GetVkPhysicalDevice();
    FVulkanCommandBuffer* GetVkCommandBuffer(int INDEX = 0);
};
