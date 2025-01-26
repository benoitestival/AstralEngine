#include "VulkanVertexBuffer.h"

#include "../VulkanDevice/VulkanDevice.h"


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
    VkDeviceSize VertexBufferSize = sizeof(Vertices[0]) * Vertices.Lenght();

    //Staging Buffer
    VkBuffer StagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory StagingBufferMemory = VK_NULL_HANDLE;
    CreateBuffer(VertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);

    void* Data = nullptr;
    vkMapMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory, 0, VertexBufferSize, 0, &Data);
    memcpy(Data, Vertices.Data(), (size_t)VertexBufferSize);
    vkUnmapMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory);
    
    CreateBuffer(VertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, GetPrivateRessource(), GetPrivateMemoryRessource());

    CopyBuffer(StagingBuffer, GetPrivateRessource(), VertexBufferSize);

    vkDestroyBuffer(GetVkDevice()->GetPrivateRessource(), StagingBuffer, nullptr);
    vkFreeMemory(GetVkDevice()->GetPrivateRessource(), StagingBufferMemory, nullptr);
    
    return VK_SUCCESS;
}

void FVulkanVertexBuffer::Clean() {
    vkDestroyBuffer(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
    vkFreeMemory(GetVkDevice()->GetPrivateRessource(), GetPrivateMemoryRessource(), nullptr);
}

int FVulkanVertexBuffer::GetNumVertices() const {
    return Vertices.Lenght();
}


