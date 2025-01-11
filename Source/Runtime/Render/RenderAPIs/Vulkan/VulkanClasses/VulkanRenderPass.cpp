#include "VulkanRenderPass.h"

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"
#include "../VulkanRenderer.h"
#include "../../../../Engine/Statics/GameplayStatics.h"

FVulkanRenderPass::FVulkanRenderPass() {
}

FVulkanRenderPass::~FVulkanRenderPass() {
}

VkResult FVulkanRenderPass::Init() {
    VkAttachmentDescription ColorAttachment = {};
    ColorAttachment.format = GetVkSwapChain()->GetFormat();
    ColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

    //Option for what to do before rendering
    ColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; 
    ColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    ColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    ColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


    VkAttachmentReference ColorAttachmentRef = {};
    ColorAttachmentRef.attachment = 0;
    ColorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription SubPass = {};
    SubPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    SubPass.colorAttachmentCount = 1;
    SubPass.pColorAttachments = &ColorAttachmentRef;

    VkSubpassDependency SubPassDependency = {};
    SubPassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    SubPassDependency.dstSubpass = 0;
    SubPassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    SubPassDependency.srcAccessMask = 0;
    SubPassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    SubPassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    
    VkRenderPassCreateInfo RenderPassInfo = {};
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassInfo.attachmentCount = 1;
    RenderPassInfo.pAttachments = &ColorAttachment;
    RenderPassInfo.subpassCount = 1;
    RenderPassInfo.pSubpasses = &SubPass;
    RenderPassInfo.dependencyCount = 1;
    RenderPassInfo.pDependencies = &SubPassDependency;
    

    return vkCreateRenderPass(GetVkDevice()->GetPrivateRessource(), &RenderPassInfo, nullptr, &GetPrivateRessource());
}

void FVulkanRenderPass::Clean() {
    vkDestroyRenderPass(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
}


FVulkanDevice* FVulkanRenderPass::GetVkDevice() const {
    return GetVKRenderer()->GetVkDevice();
}

FVulkanSwapChain* FVulkanRenderPass::GetVkSwapChain() const {
    return GetVKRenderer()->GetVkSwapChain();
}
