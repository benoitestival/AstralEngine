#include "VulkanIndexBuffer.h"

#include "../VulkanDevice/VulkanDevice.h"

FVulkanIndexBuffer::FVulkanIndexBuffer() {
    Indices = {
        0,
        1,
        2
    };
}

FVulkanIndexBuffer::~FVulkanIndexBuffer() {
}

VkResult FVulkanIndexBuffer::Init() {
    VkDeviceSize IndexBufferSize = sizeof(Indices[0]) * Indices.Lenght();

    VkBuffer StagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory StagingBufferMemory = VK_NULL_HANDLE;
    CreateBuffer(IndexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);

    void* Data = nullptr;
    vkMapMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory, 0, IndexBufferSize, 0, &Data);
    memcpy(Data, Indices.Data(), (size_t)IndexBufferSize);
    vkUnmapMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory);

    CreateBuffer(IndexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, GetPrivateRessource(), GetPrivateMemoryRessource());

    CopyBuffer(StagingBuffer, GetPrivateRessource(), IndexBufferSize);

    vkDestroyBuffer(GetVkDevice()->GetPrivateRessource(), StagingBuffer, nullptr);
    vkFreeMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory, nullptr);
    
    return VK_SUCCESS;
}

void FVulkanIndexBuffer::Clean() {
    vkDestroyBuffer(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
    vkFreeMemory(GetVkDevice()->GetPrivateRessource(), GetPrivateMemoryRessource(), nullptr);
}

int FVulkanIndexBuffer::GetNumIndices() const {
    return Indices.Lenght();
}
