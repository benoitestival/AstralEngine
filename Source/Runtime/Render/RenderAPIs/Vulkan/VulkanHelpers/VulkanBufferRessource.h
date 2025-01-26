#pragma once
#include "VulkanRessource.h"


template<class T, class MemoryRessource>
class TVulkanBufferRessource : public TVulkanRessource<T>{
public:
    TVulkanBufferRessource() = default;

    MemoryRessource& GetPrivateMemoryRessource(){
        return VulkanMemoryRessource;
    }

private:
    MemoryRessource VulkanMemoryRessource;
};
