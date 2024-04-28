#pragma once
#include "../../Objects/BaseObject.h"

class AInpuManager : public ABaseObject{
public:
    DECLARE_RTTI(AInpuManager)

private:
    AInpuManager();
    static AInpuManager* InputManager;
public:
    ~AInpuManager() override;
    static AInpuManager* Get();
    
};
