#pragma once
#include "../VulkanObject.h"
#include "../VulkanHelpers/VulkanRessource.h"

class FVulkanPhysicalDevice;
class FVulkanDevice;

class FVulkanVertexBuffer : public FVulkanObject, public TVulkanRessource<VkBuffer> {
public:
    FVulkanVertexBuffer();
    ~FVulkanVertexBuffer() override;

    virtual VkResult Init() override;
    virtual void Clean() override;

    int GetNumVertex() const;
private:
    uint32_t FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties);
private:
    FVulkanDevice* GetVkDevice();
    FVulkanPhysicalDevice* GetVkPhysicalDevice();

private:
    TArray<FVertex> Vertices;
    VkDeviceMemory VertexBufferMemory = VK_NULL_HANDLE;
};
