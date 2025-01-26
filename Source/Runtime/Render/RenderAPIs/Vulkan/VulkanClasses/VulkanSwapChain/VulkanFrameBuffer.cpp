#include "VulkanFrameBuffer.h"

#include "../../VulkanRenderer.h"
#include "../VulkanDevice/VulkanDevice.h"
#include "../VulkanRenderPass/VulkanRenderPass.h"
#include "VulkanSwapChain.h"


FVulkanFrameBuffer::FVulkanFrameBuffer(){
}

FVulkanFrameBuffer::FVulkanFrameBuffer(const TArray<VkImageView>& Attachements) {
    LinkedAttachement = Attachements;
}

FVulkanFrameBuffer::~FVulkanFrameBuffer() {
}

VkResult FVulkanFrameBuffer::Init() {
    VkFramebufferCreateInfo FramebufferInfo{};
    FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    FramebufferInfo.renderPass = GetVkRenderPass()->GetPrivateRessource();
    FramebufferInfo.attachmentCount = 1;
    FramebufferInfo.pAttachments = LinkedAttachement.Data();
    FramebufferInfo.width = GetVkSwapChain()->GetExtent().width;
    FramebufferInfo.height = GetVkSwapChain()->GetExtent().height;
    FramebufferInfo.layers = 1;

    return vkCreateFramebuffer(GetVkDevice()->GetPrivateRessource(), &FramebufferInfo, nullptr, &GetPrivateRessource());
}

void FVulkanFrameBuffer::Clean() {
    vkDestroyFramebuffer(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);    
}

FVulkanRenderPass* FVulkanFrameBuffer::GetVkRenderPass() const {
    return GetVKRenderer()->GetVkRenderPass();
}

FVulkanSwapChain* FVulkanFrameBuffer::GetVkSwapChain() const {
    return GetVKRenderer()->GetVkSwapChain();
}

FVulkanDevice* FVulkanFrameBuffer::GetVkDevice() const {
    return GetVKRenderer()->GetVkDevice();
}
