#include "VulkanTypes.h"

VkVertexInputBindingDescription FVertex::GetBindingDescription() {
    VkVertexInputBindingDescription BindingDescription = {};
    BindingDescription.binding = 0;
    BindingDescription.stride = sizeof(FVertex);
    BindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return BindingDescription;
}

TArray<VkVertexInputAttributeDescription> FVertex::GetAttributeDescriptions() {
    TArray<VkVertexInputAttributeDescription> AttributeDescriptions = {};
    AttributeDescriptions.Resize(2);

    AttributeDescriptions[0].binding = 0;
    AttributeDescriptions[0].location = 0;
    AttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    AttributeDescriptions[0].offset = offsetof(FVertex, Position);

    AttributeDescriptions[1].binding = 0;
    AttributeDescriptions[1].location = 1;
    AttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    AttributeDescriptions[1].offset = offsetof(FVertex, Color);
    
    return AttributeDescriptions;
}
