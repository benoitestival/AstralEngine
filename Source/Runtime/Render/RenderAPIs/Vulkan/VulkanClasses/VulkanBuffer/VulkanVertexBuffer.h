#pragma once
#include "VulkanBaseBuffer.h"


class FVulkanPhysicalDevice;
class FVulkanDevice;

class FVulkanVertexBuffer : public FVulkanBaseBuffer {
public:
    FVulkanVertexBuffer();
    ~FVulkanVertexBuffer() override;

    virtual VkResult Init() override;
    virtual void Clean() override;

    int GetNumVertices() const;

private:
    TArray<FVertex> Vertices;
};
