#pragma once
#include "../RTTI/Field.h"

//Static class for help and loading configs
class ConfigUtils {
public:
    static FClass* GetEngineClass();
    static FClass* GetInputManagerClass();
    static FClass* GetRenderManagerClass();
};
