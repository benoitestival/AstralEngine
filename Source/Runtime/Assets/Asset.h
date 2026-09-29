#pragma once
#include "../RTTI/Guid.h"
#include "../Utils/Path/Path.h"

class ABaseObject;
struct FClass;

struct FAsset {
    
    FAsset() = default;
public:
    FGuid AssetID;
    FPath AssetPath;
    
    FClass* AssetClass;
    ABaseObject* AssetLoadedObject;
};

