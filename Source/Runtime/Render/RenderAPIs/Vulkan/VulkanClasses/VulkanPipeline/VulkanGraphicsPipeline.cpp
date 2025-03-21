// ReSharper disable All
#include "VulkanGraphicsPipeline.h"

#include <fstream>
#include "../../../../ShaderSystem/Vulkan/VulkanShader.h"
#include "../../../../ShaderSystem/ShaderManager.h"
#include "../../VulkanRenderer.h"
#include "../VulkanDevice/VulkanDevice.h"
#include "../VulkanRenderPass/VulkanRenderPass.h"
#include "../VulkanSwapChain/VulkanSwapChain.h"
#include "VulkanPipelineLayout.h"




FVulkanGraphicsPipeline::FVulkanGraphicsPipeline() {
}

FVulkanGraphicsPipeline::~FVulkanGraphicsPipeline() {
}

VkResult FVulkanGraphicsPipeline::Init() {
    VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo = {};
    
    GraphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    GraphicsPipelineCreateInfo.stageCount = 2;
    TArray<VkPipelineShaderStageCreateInfo> StagesCreateInfo = CreateShaderStagesInfos();
    GraphicsPipelineCreateInfo.pStages = StagesCreateInfo.Data();
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineVertexInputStateCreateInfo VertexInputInfos = CreatePipelineVertexInputInfos();
    VkVertexInputBindingDescription BindingDescription = FVertex::GetBindingDescription();
    VertexInputInfos.pVertexBindingDescriptions = &BindingDescription;
    TArray<VkVertexInputAttributeDescription> AttributeDescriptions = FVertex::GetAttributeDescriptions();
    VertexInputInfos.pVertexAttributeDescriptions = AttributeDescriptions.Data();
    GraphicsPipelineCreateInfo.pVertexInputState = &VertexInputInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfos = CreatePipelineInputAssemblyInfos();
    GraphicsPipelineCreateInfo.pInputAssemblyState = &InputAssemblyInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineViewportStateCreateInfo ViewportStateInfos = CreatePipelineViewportStateInfos();
    GraphicsPipelineCreateInfo.pViewportState = &ViewportStateInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineRasterizationStateCreateInfo RasterizationStateInfos = CreatePipelineRasterizationStateInfos();
    GraphicsPipelineCreateInfo.pRasterizationState = &RasterizationStateInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineMultisampleStateCreateInfo MultisamplingStateInfos = CreatePipelineMultisamplingStateInfos();
    GraphicsPipelineCreateInfo.pMultisampleState = &MultisamplingStateInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineColorBlendAttachmentState ColorBlendAttachments = CreatePipelineColorBlendAttachmentsState();
    VkPipelineColorBlendStateCreateInfo ColorBlendStateInfos = CreatePipelineColorBlendStateInfos();
    ColorBlendStateInfos.pAttachments = &ColorBlendAttachments;
    GraphicsPipelineCreateInfo.pColorBlendState = &ColorBlendStateInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    VkPipelineDynamicStateCreateInfo DynamicStateInfos = CreatePipelineDynamicStateInfos();
    GraphicsPipelineCreateInfo.pDynamicState = &DynamicStateInfos;
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    GraphicsPipelineCreateInfo.layout = CreatePipelineLayout()->GetPrivateRessource();
    
    ///////////////////////////////////////////////////////////////////////////////////
    
    GraphicsPipelineCreateInfo.renderPass = GetVkRenderPass()->GetPrivateRessource();
    GraphicsPipelineCreateInfo.subpass = 0;
    
    GraphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    GraphicsPipelineCreateInfo.basePipelineIndex = -1;
    
    return vkCreateGraphicsPipelines(GetVkDevice()->GetPrivateRessource(), VK_NULL_HANDLE, 1, &GraphicsPipelineCreateInfo, nullptr, &GetPrivateRessource());
}

void FVulkanGraphicsPipeline::Clean() {
    GetVKRenderer()->GetShaderManager()->ClearShaders();
    CleanPipelineLayout();
    vkDestroyPipeline(GetVkDevice()->GetPrivateRessource(), GetPrivateRessource(), nullptr);
}


TArray<VkPipelineShaderStageCreateInfo> FVulkanGraphicsPipeline::CreateShaderStagesInfos() {
    
    AVulkanShader* VertexShader = GetVKRenderer()->GetShaderManager()->CreateShaderFromPath<AVulkanShader>(MAKE_FILE_PATH(FPathUtils::GetEngineShadersPath(), "vert", "spv"));
    AVulkanShader* PixelShader = GetVKRenderer()->GetShaderManager()->CreateShaderFromPath<AVulkanShader>(MAKE_FILE_PATH(FPathUtils::GetEngineShadersPath(), "frag", "spv"));

    VkPipelineShaderStageCreateInfo VertShaderStageInfo = CreatePipelineShaderStageInfos(VK_SHADER_STAGE_VERTEX_BIT, VertexShader);
    VkPipelineShaderStageCreateInfo FragShaderStageInfo = CreatePipelineShaderStageInfos(VK_SHADER_STAGE_FRAGMENT_BIT, PixelShader);

    return {VertShaderStageInfo, FragShaderStageInfo};
}

VkPipelineShaderStageCreateInfo FVulkanGraphicsPipeline::CreatePipelineShaderStageInfos(VkShaderStageFlagBits Stage, AVulkanShader* Shader) {
    VkPipelineShaderStageCreateInfo ShaderStageInfos = {};
    ShaderStageInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    ShaderStageInfos.stage = Stage;
    ShaderStageInfos.module = Shader->GetPrivateShader();
    ShaderStageInfos.pName = "main";

    return ShaderStageInfos;
}

VkPipelineVertexInputStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineVertexInputInfos() {
    VkPipelineVertexInputStateCreateInfo VertexInputInfos = {};
    VertexInputInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputInfos.vertexBindingDescriptionCount = 0;
    VertexInputInfos.vertexAttributeDescriptionCount = 0;

    VertexInputInfos.vertexBindingDescriptionCount = 1;

    VertexInputInfos.vertexAttributeDescriptionCount = FVertex::GetAttributeDescriptions().Lenght();
    
    return VertexInputInfos;
}

VkPipelineInputAssemblyStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineInputAssemblyInfos() {
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfos = {};
    InputAssemblyInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssemblyInfos.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    InputAssemblyInfos.primitiveRestartEnable = VK_FALSE;
    return InputAssemblyInfos;
}

VkPipelineViewportStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineViewportStateInfos(bool UseDynamicState) {
    VkPipelineViewportStateCreateInfo ViewportStateInfos = {};
    if (UseDynamicState) {
        ViewportStateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        ViewportStateInfos.viewportCount = 1;
        ViewportStateInfos.scissorCount = 1;
    }
    else {
        VkViewport Viewport = {};
        Viewport.x = 0.0f;
        Viewport.y = 0.0f;
        Viewport.width = GetVkSwapChain()->GetExtent().width;
        Viewport.height = GetVkSwapChain()->GetExtent().height;
        Viewport.minDepth = 0.0f;
        Viewport.maxDepth = 1.0f;
        
        VkRect2D Scissor = {};
        Scissor.offset = {0, 0};
        Scissor.extent = GetVkSwapChain()->GetExtent();
        
        ViewportStateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        ViewportStateInfos.viewportCount = 1;
        ViewportStateInfos.pViewports = &Viewport;
        ViewportStateInfos.scissorCount = 1;
        ViewportStateInfos.pScissors = &Scissor;
    }
    return ViewportStateInfos;
}

VkPipelineRasterizationStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineRasterizationStateInfos() {
    VkPipelineRasterizationStateCreateInfo RasterizerCreateInfos = {};
    RasterizerCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RasterizerCreateInfos.depthClampEnable = VK_FALSE;

    RasterizerCreateInfos.rasterizerDiscardEnable = VK_FALSE;
    RasterizerCreateInfos.polygonMode = VK_POLYGON_MODE_FILL;

    RasterizerCreateInfos.lineWidth = 1.0f;

    RasterizerCreateInfos.cullMode = VK_CULL_MODE_BACK_BIT;
    RasterizerCreateInfos.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

    RasterizerCreateInfos.depthBiasEnable = VK_FALSE;

    return RasterizerCreateInfos;
}

VkPipelineMultisampleStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineMultisamplingStateInfos() {
    VkPipelineMultisampleStateCreateInfo MultisamplingCreateInfos = {};
    MultisamplingCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    MultisamplingCreateInfos.sampleShadingEnable = VK_FALSE;
    MultisamplingCreateInfos.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    return MultisamplingCreateInfos;
}

VkPipelineColorBlendAttachmentState FVulkanGraphicsPipeline::CreatePipelineColorBlendAttachmentsState() {
    VkPipelineColorBlendAttachmentState ColorBlendAttachment = {};
    ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    ColorBlendAttachment.blendEnable = VK_FALSE;
    return ColorBlendAttachment;
}

VkPipelineColorBlendStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineColorBlendStateInfos() {
    VkPipelineColorBlendStateCreateInfo ColorBlendingCreateInfos{};
    ColorBlendingCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendingCreateInfos.logicOpEnable = VK_FALSE;
    ColorBlendingCreateInfos.logicOp = VK_LOGIC_OP_COPY;
    ColorBlendingCreateInfos.attachmentCount = 1;
    ColorBlendingCreateInfos.blendConstants[0] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[1] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[2] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[3] = 0.0f;

    return ColorBlendingCreateInfos;
}

VkPipelineDynamicStateCreateInfo FVulkanGraphicsPipeline::CreatePipelineDynamicStateInfos() {
    VkPipelineDynamicStateCreateInfo DynamicStateInfos = {};
    DynamicStateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicStateInfos.dynamicStateCount = static_cast<uint32_t>(DynamicStates.Lenght());
    DynamicStateInfos.pDynamicStates = DynamicStates.Data();
    return DynamicStateInfos;
}

FVulkanPipelineLayout* FVulkanGraphicsPipeline::CreatePipelineLayout() {
    if (VulkanPipelineLayout == nullptr) {
        FVulkanPipelineLayout* PipelineLayout = new FVulkanPipelineLayout();
        PipelineLayout->Init();
        VulkanPipelineLayout = PipelineLayout;
    }
    return VulkanPipelineLayout;
}

void FVulkanGraphicsPipeline::CleanPipelineLayout() {
    VulkanPipelineLayout->Clean();
    delete VulkanPipelineLayout;
    VulkanPipelineLayout = nullptr;
}

FVulkanDevice* FVulkanGraphicsPipeline::GetVkDevice() const {
    return GetVKRenderer()->GetVkDevice();
}

FVulkanSwapChain* FVulkanGraphicsPipeline::GetVkSwapChain() {
    return GetVKRenderer()->GetVkSwapChain();
}

FVulkanRenderPass* FVulkanGraphicsPipeline::GetVkRenderPass() const {
    return GetVKRenderer()->GetVkRenderPass();
}
