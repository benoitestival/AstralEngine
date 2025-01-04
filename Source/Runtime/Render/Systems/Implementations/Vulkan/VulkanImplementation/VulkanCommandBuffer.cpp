#include "VulkanCommandBuffer.h"

#include "VulkanDevice.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanRenderPass.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

FVulkanCommandBuffer::FVulkanCommandBuffer() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
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

    return vkAllocateCommandBuffers(GetVkDevice()->GetPrivateLogicalDevice(), &BufferAllocateInfo, &CommandBuffer);
}

void FVulkanCommandBuffer::Clean() {
    CleanCommandPool();
}

VkResult FVulkanCommandBuffer::CreateCommandPool() {
    FQueueFamilyIndices SupportedQueueFamilyIndices = GetVkDevice()->GetSupportedQueueFamilies();

    VkCommandPoolCreateInfo CommandPoolInfo{};
    CommandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    CommandPoolInfo.queueFamilyIndex = SupportedQueueFamilyIndices.GraphicsFamilyIndice;

    return vkCreateCommandPool(GetVkDevice()->GetPrivateLogicalDevice(), &CommandPoolInfo, nullptr, &CommandPool);
}

void FVulkanCommandBuffer::CleanCommandPool() {
    vkDestroyCommandPool(GetVkDevice()->GetPrivateLogicalDevice(), CommandPool, nullptr);
}

VkResult FVulkanCommandBuffer::RecordRenderPassCommand(int FRAME_INDEX) {
    VkCommandBufferBeginInfo CommandBufferBeginInfo{};
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.flags = 0;
    CommandBufferBeginInfo.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(CommandBuffer, &CommandBufferBeginInfo);

    VkRenderPassBeginInfo RenderPassBeginInfo{};
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.renderPass = GetVkRenderPass()->GetPrivateRenderPass();
    RenderPassBeginInfo.framebuffer = GetVkSwapChain()->GetFrameBuffer(FRAME_INDEX)->GetPrivateFrameBuffer();

    RenderPassBeginInfo.renderArea.offset = {0, 0};
    RenderPassBeginInfo.renderArea.extent = GetVkSwapChain()->GetExtent();

    VkClearValue ClearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};//Black
    RenderPassBeginInfo.clearValueCount = 1;
    RenderPassBeginInfo.pClearValues = &ClearColor;

    //Start the render pass
    vkCmdBeginRenderPass(CommandBuffer, &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    
    vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GetVkGraphicsPipeline()->GetPrivateGraphicsPipeline());

    VkViewport Viewport = GetVkSwapChain()->GetViewport();
    vkCmdSetViewport(CommandBuffer, 0, 1, &Viewport);

    VkRect2D Scissor = GetVkSwapChain()->GetScissor();
    vkCmdSetScissor(CommandBuffer, 0, 1, &Scissor);

    vkCmdDraw(CommandBuffer, 3, 1, 0, 0);

    //End the render pass
    vkCmdEndRenderPass(CommandBuffer);

    return vkEndCommandBuffer(CommandBuffer);
}

VkCommandBuffer FVulkanCommandBuffer::GetPrivateCommandBuffer() const {
    return CommandBuffer;
}

AVulkanRenderManager* FVulkanCommandBuffer::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanCommandBuffer::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}

FVulkanRenderPass* FVulkanCommandBuffer::GetVkRenderPass() const {
    return GetRenderManager()->GetVkRenderPass();
}

FVulkanSwapChain* FVulkanCommandBuffer::GetVkSwapChain() const {
    return GetRenderManager()->GetVkSwapChain();
}

FVulkanGraphicsPipeline* FVulkanCommandBuffer::GetVkGraphicsPipeline() const {
    return GetRenderManager()->GetVkGraphicsPipeline();
}
