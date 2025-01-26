#pragma once
#include "VulkanBaseBuffer.h"

class FVulkanIndexBuffer : public FVulkanBaseBuffer {
public:
    FVulkanIndexBuffer();
    ~FVulkanIndexBuffer() override;

    virtual VkResult Init() override;
    virtual void Clean() override;

    int GetNumIndices() const;

private:
    TArray<uint16_t> Indices;
};
