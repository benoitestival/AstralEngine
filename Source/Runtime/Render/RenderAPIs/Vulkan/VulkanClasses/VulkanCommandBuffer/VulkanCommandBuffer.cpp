#include "VulkanCommandBuffer.h"


#include "../../VulkanRenderer.h"
#include "../VulkanDevice/VulkanDevice.h"
#include "../VulkanDevice/VulkanPhysicalDevice.h"
#include "../VulkanBuffer/VulkanVertexBuffer.h"
#include "../VulkanPipeline/VulkanGraphicsPipeline.h"
#include "../VulkanRenderPass/VulkanRenderPass.h"
#include "../VulkanSwapChain/VulkanFrameBuffer.h"
#include "../VulkanSwapChain/VulkanSwapChain.h"

FVulkanCommandBuffer::FVulkanCommandBuffer() {
}

FVulkanCommandBuffer::~FVulkanCommandBuffer() {
}

VkResult FVulkanCommandBuffer::Init() {
    CreateCommandPool();

    VkCommandBufferAllocateInfo BufferAllocateInfo{};
    BufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    BufferAllocateInfo.commandPool = CommandPool;
    BufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    BufferAllocateInfo.commandBufferCount = 1;

    return vkAllocateCommandBuffers(GetVkDevice()->GetPrivateRessource(), &BufferAllocateInfo, &GetPrivateRessource());
}

void FVulkanCommandBuffer::Clean() {
    CleanCommandPool();
}

VkResult FVulkanCommandBuffer::CreateCommandPool() {
    FQueueFamilyIndices SupportedQueueFamilyIndices = GetVkDevice()->GetVkPhysicalDevice()->GetSupportedQueueFamilies();

    VkCommandPoolCreateInfo CommandPoolInfo{};
    CommandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    CommandPoolInfo.queueFamilyIndex = SupportedQueueFamilyIndices.GraphicsFamilyIndice;

    return vkCreateCommandPool(GetVkDevice()->GetPrivateRessource(), &CommandPoolInfo, nullptr, &CommandPool);
}

void FVulkanCommandBuffer::CleanCommandPool() {
    vkDestroyCommandPool(GetVkDevice()->GetPrivateRessource(), CommandPool, nullptr);
}

VkResult FVulkanCommandBuffer::RecordRenderPassCommand(int FRAME_INDEX) {
    VkCommandBufferBeginInfo CommandBufferBeginInfo = {};
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(GetPrivateRessource(), &CommandBufferBeginInfo);

    VkRenderPassBeginInfo RenderPassBeginInfo = {};
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.renderPass = GetVkRenderPass()->GetPrivateRessource();
    RenderPassBeginInfo.framebuffer = GetVkSwapChain()->GetFrameBuffer(FRAME_INDEX)->GetPrivateRessource();

    RenderPassBeginInfo.renderArea.offset = {0, 0};
    RenderPassBeginInfo.renderArea.extent = GetVkSwapChain()->GetExtent();

    VkClearValue ClearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};//Black
    RenderPassBeginInfo.clearValueCount = 1;
    RenderPassBeginInfo.pClearValues = &ClearColor;

    //Start the render pass
    vkCmdBeginRenderPass(GetPrivateRessource(), &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    vkCmdBindPipeline(GetPrivateRessource(), VK_PIPELINE_BIND_POINT_GRAPHICS, GetVkGraphicsPipeline()->GetPrivateRessource());
    
    VkViewport Viewport = GetVkSwapChain()->GetViewport();
    vkCmdSetViewport(GetPrivateRessource(), 0, 1, &Viewport);

    VkRect2D Scissor = GetVkSwapChain()->GetScissor();
    vkCmdSetScissor(GetPrivateRessource(), 0, 1, &Scissor);

    TArray<VkBuffer> VertexBuffers = {GetVkVertexBuffer()->GetPrivateRessource()};
    TArray<VkDeviceSize> Offsets = {0};
    
    vkCmdBindVertexBuffers(GetPrivateRessource(), 0, 1, VertexBuffers.Data(), Offsets.Data());
    
    vkCmdDraw(GetPrivateRessource(), GetVkVertexBuffer()->GetNumVertex(), 1, 0, 0);

    //End the render pass
    vkCmdEndRenderPass(GetPrivateRessource());

    return vkEndCommandBuffer(GetPrivateRessource());
}

VkCommandPool& FVulkanCommandBuffer::GetCommandPool() {
    return CommandPool;
}

FVulkanDevice* FVulkanCommandBuffer::GetVkDevice() const {
    return GetVKRenderer()->GetVkDevice();
}

FVulkanRenderPass* FVulkanCommandBuffer::GetVkRenderPass() const {
    return GetVKRenderer()->GetVkRenderPass();
}

FVulkanSwapChain* FVulkanCommandBuffer::GetVkSwapChain() const {
    return GetVKRenderer()->GetVkSwapChain();
}

FVulkanGraphicsPipeline* FVulkanCommandBuffer::GetVkGraphicsPipeline() const {
    return GetVKRenderer()->GetVkGraphicsPipeline();
}

FVulkanVertexBuffer* FVulkanCommandBuffer::GetVkVertexBuffer() const {
    return GetVKRenderer()->GetVkVertexBuffer();
}
