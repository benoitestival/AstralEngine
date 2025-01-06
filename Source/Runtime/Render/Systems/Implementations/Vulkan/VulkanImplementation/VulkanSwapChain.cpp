#include "VulkanSwapChain.h"

#include <algorithm>
#include <GLFW/glfw3.h>

#include "VulkanDevice.h"
#include "VulkanFrameBuffer.h"
#include "VulkanSurface.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Engine/Engine.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"
#include "../../../../../Window/Implementations/GLFWWindow.h"

FVulkanSwapChain::FVulkanSwapChain(): SwapChainImageFormat(), SwapChainExtent() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanSwapChain::~FVulkanSwapChain() {
}

VkResult FVulkanSwapChain::Init() {
    FSwapChainSupportDetails SwapChainSupportDetails = GetVkDevice()->QuerySwapChainSupportDetails();

    VkSurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(SwapChainSupportDetails.Formats);
    VkPresentModeKHR PresentMode = ChooseSwapPresentMode(SwapChainSupportDetails.PresentModes);
    VkExtent2D Extent = ChooseSwapExtent(SwapChainSupportDetails.Capabilities);

    //Number of image contain in the SwapChain
    uint32_t ImageCount = SwapChainSupportDetails.Capabilities.minImageCount + 1;//+1 for requesting one more image, with that we dont always have o wait the driver
    if (ImageCount > SwapChainSupportDetails.Capabilities.maxImageCount && SwapChainSupportDetails.Capabilities.maxImageCount > 0) {
        //Just in case where the min is superior to the max image count allowed
        ImageCount = SwapChainSupportDetails.Capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR SwapChainCreateInfo{};
    SwapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    SwapChainCreateInfo.surface = GetVkSurface()->GetPrivateSurface();

    SwapChainCreateInfo.minImageCount = ImageCount;
    SwapChainCreateInfo.imageFormat = SurfaceFormat.format;
    SwapChainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
    SwapChainCreateInfo.imageExtent = Extent;
    SwapChainCreateInfo.imageArrayLayers = 1;
    SwapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    FQueueFamilyIndices SupportedQueueFamilyIndices = GetVkDevice()->GetSupportedQueueFamilies();
    TArray<uint32_t> QueueFamilyIndices = SupportedQueueFamilyIndices.ToUnsignedArray();
    
    if (SupportedQueueFamilyIndices.GraphicsFamilyIndice != SupportedQueueFamilyIndices.PresentingFamilyIndice) {
        SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        SwapChainCreateInfo.queueFamilyIndexCount = 2;
        
        SwapChainCreateInfo.pQueueFamilyIndices = QueueFamilyIndices.Data();
    } else {
        SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        SwapChainCreateInfo.queueFamilyIndexCount = 0; // Optional
        SwapChainCreateInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    SwapChainCreateInfo.preTransform = SwapChainSupportDetails.Capabilities.currentTransform;
    SwapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    SwapChainCreateInfo.presentMode = PresentMode;
    SwapChainCreateInfo.clipped = VK_TRUE;

    SwapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    vkCreateSwapchainKHR(GetVkDevice()->GetPrivateLogicalDevice(), &SwapChainCreateInfo, nullptr, &SwapChain);
    
    vkGetSwapchainImagesKHR(GetVkDevice()->GetPrivateLogicalDevice(), SwapChain, &ImageCount, nullptr);
    SwapChainImages.Resize(ImageCount);
    vkGetSwapchainImagesKHR(GetVkDevice()->GetPrivateLogicalDevice(), SwapChain, &ImageCount, SwapChainImages.Data());

    SwapChainImageFormat = SurfaceFormat.format;
    SwapChainExtent = Extent;
    
    return VK_SUCCESS;
}

void FVulkanSwapChain::Clean() {
    vkDestroySwapchainKHR(GetVkDevice()->GetPrivateLogicalDevice(), SwapChain, nullptr);
}

VkResult FVulkanSwapChain::InitImageViews() {
    VkResult FinalResult = VK_SUCCESS;
    SwapChainImageViews.Resize(SwapChainImages.Lenght());
    for (int SWAP_CHAIN_IMAGE_INDEX = 0; SWAP_CHAIN_IMAGE_INDEX < SwapChainImages.Lenght(); SWAP_CHAIN_IMAGE_INDEX++) {
        VkImageViewCreateInfo ImageViewCreateInfo{};
        ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        ImageViewCreateInfo.image = SwapChainImages[SWAP_CHAIN_IMAGE_INDEX];

        ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        ImageViewCreateInfo.format = SwapChainImageFormat;

        ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        ImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        ImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        ImageViewCreateInfo.subresourceRange.levelCount = 1;
        ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        ImageViewCreateInfo.subresourceRange.layerCount = 1;

        VkResult Result = vkCreateImageView(GetVkDevice()->GetPrivateLogicalDevice(), &ImageViewCreateInfo, nullptr, &SwapChainImageViews[SWAP_CHAIN_IMAGE_INDEX]);
        if (Result != VK_SUCCESS) {
            FinalResult = Result;
            break;
        }
    }
    return FinalResult;
}

void FVulkanSwapChain::CleanImageViews() {
    for (auto& SwapChainImageView : SwapChainImageViews) {
        vkDestroyImageView(GetVkDevice()->GetPrivateLogicalDevice(), SwapChainImageView, nullptr);
    }
    SwapChainImageViews.Clear();
}

VkResult FVulkanSwapChain::InitFrameBuffers() {
    VkResult FinalResult = VK_SUCCESS;
    SwapChainFrameBuffers.Resize(SwapChainImages.Lenght());
    for (int SWAP_CHAIN_IMAGE_INDEX = 0; SWAP_CHAIN_IMAGE_INDEX < SwapChainImages.Lenght(); SWAP_CHAIN_IMAGE_INDEX++) {
        FVulkanFrameBuffer* FrameBuffer = new FVulkanFrameBuffer();
        VkResult Result = FrameBuffer->Init({SwapChainImageViews[SWAP_CHAIN_IMAGE_INDEX]});
        if (Result != VK_SUCCESS) {
            FinalResult = Result;
            break;
        }
        SwapChainFrameBuffers[SWAP_CHAIN_IMAGE_INDEX] = FrameBuffer;
    }

    return FinalResult;
}

void FVulkanSwapChain::CleanFrameBuffers() {
    for (auto& FrameBuffer : SwapChainFrameBuffers) {
        FrameBuffer->Clean();
        delete FrameBuffer;
        FrameBuffer = nullptr;
    }
    SwapChainFrameBuffers.Clear();
}

VkFormat FVulkanSwapChain::GetFormat() const{
    return SwapChainImageFormat;
}

VkExtent2D FVulkanSwapChain::GetExtent() const{
    return SwapChainExtent;
}

VkViewport FVulkanSwapChain::GetViewport() const {
    VkViewport Viewport = {};
    Viewport.x = 0.0f;
    Viewport.y = 0.0f;
    Viewport.width = static_cast<float>(GetExtent().width);
    Viewport.height = static_cast<float>(GetExtent().height);
    Viewport.minDepth = 0.0f;
    Viewport.maxDepth = 1.0f;
    return Viewport;
}

VkRect2D FVulkanSwapChain::GetScissor() const {
    VkRect2D Scissor = {};
    Scissor.offset = {0, 0};
    Scissor.extent = GetExtent();
    return Scissor;
}

FVulkanFrameBuffer* FVulkanSwapChain::GetFrameBuffer(int FRAME_BUFFER_INDEX) const {
    return SwapChainFrameBuffers[FRAME_BUFFER_INDEX];
}

VkSwapchainKHR FVulkanSwapChain::GetPrivateSwapChain() const {
    return SwapChain;
}

VkSurfaceFormatKHR FVulkanSwapChain::ChooseSwapSurfaceFormat(const TArray<VkSurfaceFormatKHR>& AvailableFormats) {
    VkSurfaceFormatKHR ChoosenSurfaceFormat = AvailableFormats[0];//By default we take the first
    for (auto& Format : AvailableFormats) {
        if (Format.format == VK_FORMAT_B8G8R8A8_SRGB && Format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            ChoosenSurfaceFormat = Format;
        }
    }
    return ChoosenSurfaceFormat;
}

VkPresentModeKHR FVulkanSwapChain::ChooseSwapPresentMode(const TArray<VkPresentModeKHR>& AvailablePresentModes) {
    
    ////////////////////// VK_PRESENT_MODE_IMMEDIATE_KHR:///////////////////////////
    // Immediate Rendering.
    
    ///////////////////////// VK_PRESENT_MODE_FIFO_KHR://///////////////////////////
    // Wainting for room in the queue of the swap chain (similar to V-sync)
    
    //////////////////// VK_PRESENT_MODE_FIFO_RELAXED_KHR://////////////////////////
    // Immediate Rendering if the application is late to try removing the overtime
    
    ////////////////////// VK_PRESENT_MODE_MAILBOX_KHR://///////////////////////////
    //If there is no room in the queue of the swap chain replace the frame in the queue by the new one that is ready (similar to triple buffering) 

    VkPresentModeKHR ChoosenPresentMode = VK_PRESENT_MODE_FIFO_KHR;
    for (auto& PresentMode : AvailablePresentModes) {
        if (PresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            ChoosenPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        }
    }
    return ChoosenPresentMode;
}

VkExtent2D FVulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities) {
    VkExtent2D SwapExtent = Capabilities.currentExtent;
    
    //If the capability width is equal to the maximal value of an unsigned int then it mean that the window managers
    //let us handle the Extent of the swap chain by picking up the resolution ourself
    if (Capabilities.currentExtent.width == std::numeric_limits<uint32_t>::max()) {
        int WIDTH = -1;
        int HEIGHT = -1;
        glfwGetFramebufferSize(GetActiveWindow()->GetPrivateWindow(), &WIDTH, &HEIGHT);
        VkExtent2D ActualExtent = {(uint32_t)(WIDTH),(uint32_t)(HEIGHT)};
        ActualExtent.width = std::clamp(ActualExtent.width, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
        ActualExtent.height = std::clamp(ActualExtent.height, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);
        SwapExtent = ActualExtent;
    }
    return SwapExtent;
}

AGLFWWindow* FVulkanSwapChain::GetActiveWindow() const {
    return Cast<AGLFWWindow>(GameplayStatics::GetEngine()->GetActiveWindow());
}

AVulkanRenderManager* FVulkanSwapChain::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanSwapChain::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}

FVulkanSurface* FVulkanSwapChain::GetVkSurface() const {
    return GetRenderManager()->GetVkSurface();
}
