#include "VulkanVertexBuffer.h"

#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"
#include "../VulkanRenderer.h"

FVulkanVertexBuffer::FVulkanVertexBuffer() {
    Vertices = {
        {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}
    };
}

FVulkanVertexBuffer::~FVulkanVertexBuffer() {
}

VkResult FVulkanVertexBuffer::Init() {
    VkBufferCreateInfo BufferInfo = {};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = sizeof(Vertices[0]) * Vertices.Lenght();
    
    BufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

    BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    vkCreateBuffer(GetVkDevice()->GetPrivateRessource(), &BufferInfo, nullptr, &GetPrivateRessource());

    VkMemoryRequirements MemRequirements = {};
    vkGetBufferMemoryRequirements(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), &MemRequirements);

    VkMemoryAllocateInfo AllocInfo = {};
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.allocationSize = MemRequirements.size;
    AllocInfo.memoryTypeIndex = FindMemoryType(MemRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    vkAllocateMemory(GetVkDevice()->GetPrivateRessource(), &AllocInfo, nullptr, &VertexBufferMemory);
    vkBindBufferMemory(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), VertexBufferMemory, 0);

    void* Data = nullptr;
    vkMapMemory(GetVkDevice()->GetPrivateRessource(), VertexBufferMemory, 0, BufferInfo.size, 0, &Data);
    memcpy(Data, Vertices.Data(), (size_t) BufferInfo.size);
    vkUnmapMemory(GetVkDevice()->GetPrivateRessource(), VertexBufferMemory);

    return VK_SUCCESS;
}

void FVulkanVertexBuffer::Clean() {
    vkDestroyBuffer(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
    vkFreeMemory(GetVkDevice()->GetPrivateRessource(), VertexBufferMemory, nullptr);
}

int FVulkanVertexBuffer::GetNumVertex() const {
    return Vertices.Lenght();
}

uint32_t FVulkanVertexBuffer::FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties) {
    VkPhysicalDeviceMemoryProperties MemProperties;
    vkGetPhysicalDeviceMemoryProperties(GetVkPhysicalDevice()->GetPrivateRessource(), &MemProperties);

    uint32_t Result = INVALID_INDEX;
    for (uint32_t i = 0; i < MemProperties.memoryTypeCount; i++) {
        if (TypeFilter & (1 << i) && (MemProperties.memoryTypes[i].propertyFlags & Properties) == Properties) {
            Result = i;
            break;
        }
    }
    return Result;
}



FVulkanDevice* FVulkanVertexBuffer::GetVkDevice() {
    return GetVKRenderer()->GetVkDevice();
}

FVulkanPhysicalDevice* FVulkanVertexBuffer::GetVkPhysicalDevice() {
    return GetVKRenderer()->GetVkPhysicalDevice();
}

