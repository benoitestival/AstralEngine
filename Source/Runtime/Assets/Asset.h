#pragma once
#include "../RTTI/Guid.h"
#include "../Utils/Path/Path.h"

class ABaseObject;
struct FClass;

struct FAsset {
    
    FAsset() = default;
    
    ABaseObject* GetOrLoad();
public:
    FGuid AssetID;
    FPath AssetPath;
    
    FClass* AssetClass;
    ABaseObject* AssetLoadedObject;
};

