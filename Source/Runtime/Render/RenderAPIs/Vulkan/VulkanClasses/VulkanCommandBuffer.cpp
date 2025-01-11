#include "VulkanCommandBuffer.h"

#include "VulkanDevice.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanRenderPass.h"
#include "../VulkanRenderer.h"
#include "../../../../Engine/Statics/GameplayStatics.h"

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

    vkCmdDraw(GetPrivateRessource(), 3, 1, 0, 0);

    //End the render pass
    vkCmdEndRenderPass(GetPrivateRessource());

    return vkEndCommandBuffer(GetPrivateRessource());
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
