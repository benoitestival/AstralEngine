#include "VulkanRenderPass.h"

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"

FVulkanRenderPass::FVulkanRenderPass() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanRenderPass::~FVulkanRenderPass() {
}

VkResult FVulkanRenderPass::Init() {
    VkAttachmentDescription ColorAttachment;
    ColorAttachment.format = GetVkSwapChain()->GetFormat();
    ColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

    //Option for what to do before rendering
    ColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; 
    ColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    ColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    ColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


    VkAttachmentReference ColorAttachmentRef;
    ColorAttachmentRef.attachment = 0;
    ColorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription SubPass;
    SubPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    SubPass.colorAttachmentCount = 1;
    SubPass.pColorAttachments = &ColorAttachmentRef;

    VkRenderPassCreateInfo RenderPassInfo;
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassInfo.attachmentCount = 1;
    RenderPassInfo.pAttachments = &ColorAttachment;
    RenderPassInfo.subpassCount = 1;
    RenderPassInfo.pSubpasses = &SubPass;

    return vkCreateRenderPass(GetVkDevice()->GetPrivateLogicalDevice(), &RenderPassInfo, nullptr, &RenderPass);
}

void FVulkanRenderPass::Clean() {
    vkDestroyRenderPass(GetVkDevice()->GetPrivateLogicalDevice(), RenderPass, nullptr);
}

AVulkanRenderManager* FVulkanRenderPass::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanRenderPass::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}

FVulkanSwapChain* FVulkanRenderPass::GetVkSwapChain() const {
    return GetRenderManager()->GetVkSwapChain();
}
