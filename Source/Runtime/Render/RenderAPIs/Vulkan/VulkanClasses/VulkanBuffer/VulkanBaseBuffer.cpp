#include "VulkanBaseBuffer.h"


#include "../../VulkanRenderer.h"
#include "../VulkanDevice/VulkanDevice.h"
#include "../VulkanDevice/VulkanPhysicalDevice.h"

FVulkanBaseBuffer::FVulkanBaseBuffer() {
}

FVulkanBaseBuffer::~FVulkanBaseBuffer() {
}

VkResult FVulkanBaseBuffer::Init() {
    return FVulkanObject::Init();
}

void FVulkanBaseBuffer::Clean() {
    FVulkanObject::Clean();
}

VkResult FVulkanBaseBuffer::CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory) {
    VkBufferCreateInfo BufferInfo = {};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = Size;
    BufferInfo.usage = Usage;
    BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    vkCreateBuffer(GetVkDevice()->GetPrivateRessource(), &BufferInfo, nullptr, &Buffer);

    VkMemoryRequirements MemRequirements = {};
    vkGetBufferMemoryRequirements(GetVkDevice()->GetPrivateRessource(), Buffer, &MemRequirements);

    VkMemoryAllocateInfo AllocInfo = {};
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.allocationSize = MemRequirements.size;
    AllocInfo.memoryTypeIndex = GetMemoryType(MemRequirements.memoryTypeBits, Properties);

    vkAllocateMemory(GetVkDevice()->GetPrivateRessource(), &AllocInfo, nullptr, &BufferMemory);

    return vkBindBufferMemory(GetVkDevice()->GetPrivateRessource(), Buffer, BufferMemory, 0);
}

VkResult FVulkanBaseBuffer::CopyBuffer(VkBuffer SrcBuffer, VkBuffer DstBuffer, VkDeviceSize size) {
    VkCommandBufferAllocateInfo AllocInfo = {};
    AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    VkCommandPool TransientCommandPool = CreateTransientVkCommandPool();
    AllocInfo.commandPool = TransientCommandPool;
    AllocInfo.commandBufferCount = 1;

    VkCommandBuffer CommandBuffer;
    vkAllocateCommandBuffers(GetVkDevice()->GetPrivateRessource(), &AllocInfo, &CommandBuffer);

    VkCommandBufferBeginInfo BeginInfo = {};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
    
    VkBufferCopy CopyRegion = {};
    CopyRegion.size = size;
    vkCmdCopyBuffer(CommandBuffer, SrcBuffer, DstBuffer, 1, &CopyRegion);

    vkEndCommandBuffer(CommandBuffer);

    VkSubmitInfo SubmitInfo = {};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.commandBufferCount = 1;
    SubmitInfo.pCommandBuffers = &CommandBuffer;

    vkQueueSubmit(GetVkDevice()->GetGraphicsQueue(), 1, &SubmitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(GetVkDevice()->GetGraphicsQueue());

    vkFreeCommandBuffers(GetVkDevice()->GetPrivateRessource(), TransientCommandPool, 1, &CommandBuffer);

    return VK_SUCCESS;
}

uint32_t FVulkanBaseBuffer::GetMemoryType(uint32_t TypeFilter,VkMemoryPropertyFlags Properties) {
    VkPhysicalDeviceMemoryProperties MemProperties;
    vkGetPhysicalDeviceMemoryProperties(GetVkPhysicalDevice()->GetPrivateRessource(), &MemProperties);

    uint32_t Result = UINT32_MAX;
    for (uint32_t i = 0; i < MemProperties.memoryTypeCount; i++) {
        if (TypeFilter & (1 << i) && (MemProperties.memoryTypes[i].propertyFlags & Properties) == Properties) {
            Result = i;
            break;
        }
    }
    return Result;
}

VkCommandPool FVulkanBaseBuffer::CreateTransientVkCommandPool() {
    FQueueFamilyIndices SupportedQueueFamilyIndices = GetVkDevice()->GetVkPhysicalDevice()->GetSupportedQueueFamilies();

    VkCommandPoolCreateInfo CommandPoolInfo{};
    CommandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    CommandPoolInfo.queueFamilyIndex = SupportedQueueFamilyIndices.GraphicsFamilyIndice;

    VkCommandPool CommandPool;
    vkCreateCommandPool(GetVkDevice()->GetPrivateRessource(), &CommandPoolInfo, nullptr, &CommandPool);
    
    return CommandPool;
}

FVulkanDevice* FVulkanBaseBuffer::GetVkDevice() {
    return GetVKRenderer()->GetVkDevice();
}

FVulkanPhysicalDevice* FVulkanBaseBuffer::GetVkPhysicalDevice() {
    return GetVKRenderer()->GetVkPhysicalDevice();
}

FVulkanCommandBuffer* FVulkanBaseBuffer::GetVkCommandBuffer(int INDEX) {
    return GetVKRenderer()->GetVkCommandBuffer(INDEX);
}
