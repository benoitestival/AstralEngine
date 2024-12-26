#include "VulkanPipeline.h"

#include "VulkanShader.h"
#include "VulkanSwapChain.h"
#include "../VulkanRenderManager.h"
#include "../../../../../Engine/Statics/GameplayStatics.h"
#include "../../../../../Utils/TemplateUtils.h"

FVulkanPipeline::FVulkanPipeline() {
    RenderManager = Cast<AVulkanRenderManager>(GameplayStatics::GetRenderManager());
}

FVulkanPipeline::~FVulkanPipeline() {
}

VkResult FVulkanPipeline::Init() {

    //TODO fix the path to really load shaders
    FVulkanShader* VertexShader = CreateShader(FPath(GameplayStatics::GetEnginePath()));
    FVulkanShader* PixelShader = CreateShader(FPath(GameplayStatics::GetEnginePath()));

    VkPipelineShaderStageCreateInfo VertShaderStageInfo = CreatePipelineShaderStageInfos(VK_SHADER_STAGE_VERTEX_BIT, VertexShader);
    VkPipelineShaderStageCreateInfo FragShaderStageInfo = CreatePipelineShaderStageInfos(VK_SHADER_STAGE_FRAGMENT_BIT, PixelShader);

    TArray<VkPipelineShaderStageCreateInfo> ShaderStages = {VertShaderStageInfo, FragShaderStageInfo};

    VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo{};
    GraphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    GraphicsPipelineCreateInfo.stageCount = 2;
    GraphicsPipelineCreateInfo.pStages = ShaderStages.Data();

    
    
    DestroyShader(VertexShader);
    DestroyShader(PixelShader);
    
    return VK_SUCCESS;
}

void FVulkanPipeline::Clean() {
}

FVulkanShader* FVulkanPipeline::CreateShader(const FPath& ShaderPath) {
    FVulkanShader* Shader = new FVulkanShader(ShaderPath);
    Shader->Init();
    return Shader;
}

void FVulkanPipeline::DestroyShader(FVulkanShader* Shader) {
    Shader->Clean();
    delete Shader;
    Shader = nullptr;
}

VkPipelineShaderStageCreateInfo FVulkanPipeline::CreatePipelineShaderStageInfos(VkShaderStageFlagBits Stage, FVulkanShader* Shader) {
    VkPipelineShaderStageCreateInfo ShaderStageInfos{};
    ShaderStageInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    ShaderStageInfos.stage = Stage;
    ShaderStageInfos.module = Shader->GetPrivateShader();
    ShaderStageInfos.pName = "main";

    return ShaderStageInfos;
}

VkPipelineDynamicStateCreateInfo FVulkanPipeline::CreatePipelineDynamicStateInfos() {
    TArray<VkDynamicState> DynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo DynamicStateInfos = {};
    DynamicStateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicStateInfos.dynamicStateCount = static_cast<uint32_t>(DynamicStates.Lenght());
    DynamicStateInfos.pDynamicStates = DynamicStates.Data();
    return DynamicStateInfos;
}

VkPipelineVertexInputStateCreateInfo FVulkanPipeline::CreatePipelineVertexInputInfos() {
    VkPipelineVertexInputStateCreateInfo VertexInputInfo = {};
    VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputInfo.vertexBindingDescriptionCount = 0;
    VertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
    VertexInputInfo.vertexAttributeDescriptionCount = 0;
    VertexInputInfo.pVertexAttributeDescriptions = nullptr;
    return VertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo FVulkanPipeline::CreatePipelineInputAssemblyInfos() {
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfos = {};
    InputAssemblyInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssemblyInfos.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    InputAssemblyInfos.primitiveRestartEnable = VK_FALSE;
    return InputAssemblyInfos;
}

VkPipelineViewportStateCreateInfo FVulkanPipeline::CreatePipelineViewportStateInfos(bool UseDynamicState) {
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

VkPipelineRasterizationStateCreateInfo FVulkanPipeline::CreatePipelineRasterizationStateInfos() {
    VkPipelineRasterizationStateCreateInfo RasterizerCreateInfos = {};
    RasterizerCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RasterizerCreateInfos.depthClampEnable = VK_FALSE;

    RasterizerCreateInfos.rasterizerDiscardEnable = VK_FALSE;
    RasterizerCreateInfos.polygonMode = VK_POLYGON_MODE_FILL;

    RasterizerCreateInfos.lineWidth = 1.0f;

    RasterizerCreateInfos.cullMode = VK_CULL_MODE_BACK_BIT;
    RasterizerCreateInfos.frontFace = VK_FRONT_FACE_CLOCKWISE;

    RasterizerCreateInfos.depthBiasEnable = VK_FALSE;
    RasterizerCreateInfos.depthBiasConstantFactor = 0.0f;
    RasterizerCreateInfos.depthBiasClamp = 0.0f; 
    RasterizerCreateInfos.depthBiasSlopeFactor = 0.0f;

    return RasterizerCreateInfos;
}

VkPipelineMultisampleStateCreateInfo FVulkanPipeline::CreatePipelineMultisamplingStateInfos() {
    VkPipelineMultisampleStateCreateInfo MultisamplingCreateInfos = {};
    MultisamplingCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    MultisamplingCreateInfos.sampleShadingEnable = VK_FALSE;
    MultisamplingCreateInfos.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    MultisamplingCreateInfos.minSampleShading = 1.0f;
    MultisamplingCreateInfos.pSampleMask = nullptr; 
    MultisamplingCreateInfos.alphaToCoverageEnable = VK_FALSE;
    MultisamplingCreateInfos.alphaToOneEnable = VK_FALSE; 

    return MultisamplingCreateInfos;
}

VkPipelineColorBlendStateCreateInfo FVulkanPipeline::CreatePipelineColorBlendStateInfos() {
    VkPipelineColorBlendAttachmentState ColorBlendAttachment = {};
    ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    ColorBlendAttachment.blendEnable = VK_FALSE;
    ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    ColorBlendAttachment.blendEnable = VK_TRUE;
    ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo ColorBlendingCreateInfos{};
    ColorBlendingCreateInfos.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendingCreateInfos.logicOpEnable = VK_FALSE;
    ColorBlendingCreateInfos.logicOp = VK_LOGIC_OP_COPY;
    ColorBlendingCreateInfos.attachmentCount = 1;
    ColorBlendingCreateInfos.pAttachments = &ColorBlendAttachment;
    ColorBlendingCreateInfos.blendConstants[0] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[1] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[2] = 0.0f;
    ColorBlendingCreateInfos.blendConstants[3] = 0.0f;

    return ColorBlendingCreateInfos;
}

AVulkanRenderManager* FVulkanPipeline::GetRenderManager() const {
    return RenderManager;
}

FVulkanDevice* FVulkanPipeline::GetVkDevice() const {
    return GetRenderManager()->GetVkDevice();
}

FVulkanSwapChain* FVulkanPipeline::GetVkSwapChain() {
    return GetRenderManager()->GetVkSwapChain();
}
