#include "VulkanFrameBuffer.h"

#include "VulkanDevice.h"
#include "VulkanRenderPass.h"
#include "VulkanSwapChain.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"

FVulkanFrameBuffer::FVulkanFrameBuffer() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanFrameBuffer::~FVulkanFrameBuffer() {
}

VkResult FVulkanFrameBuffer::Init(const TArray<VkImageView>& Attachements) {
    LinkedAttachement = Attachements;

    VkFramebufferCreateInfo FramebufferInfo{};
    FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    FramebufferInfo.renderPass = GetVkRenderPass()->GetPrivateRenderPass();
    FramebufferInfo.attachmentCount = 1;
    FramebufferInfo.pAttachments = LinkedAttachement.Data();
    FramebufferInfo.width = GetVkSwapChain()->GetExtent().width;
    FramebufferInfo.height = GetVkSwapChain()->GetExtent().height;
    FramebufferInfo.layers = 1;

    return vkCreateFramebuffer(GetVkDevice()->GetPrivateLogicalDevice(), &FramebufferInfo, nullptr, &FrameBuffer);
}

void FVulkanFrameBuffer::Clean() {
    vkDestroyFramebuffer(GetVkDevice()->GetPrivateLogicalDevice(), FrameBuffer, nullptr);    
}

VkFramebuffer FVulkanFrameBuffer::GetPrivateFrameBuffer() {
    return FrameBuffer;
}


AVulkanRenderManager* FVulkanFrameBuffer::GetRenderManager() const {
    return RenderManager;
}

FVulkanRenderPass* FVulkanFrameBuffer::GetVkRenderPass() const {
    return GetRenderManager()->GetVkRenderPass();
}

FVulkanSwapChain* FVulkanFrameBuffer::GetVkSwapChain() const {
    return GetRenderManager()->GetVkSwapChain();
}

FVulkanDevice* FVulkanFrameBuffer::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}
