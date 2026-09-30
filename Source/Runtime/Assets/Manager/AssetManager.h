#pragma once
#include "../Asset.h"
#include "../../Engine/CoreObjects/Systems/EngineSystem.h"

class AAssetManager : public AEngineSystem  {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AAssetManager, AEngineSystem)

    virtual void Init() override;
    virtual void DeInit() override;
    
    FAsset GetAssetFromID(const FGuid& AssetID);
    ABaseObject* LoadObjectFromID(const FGuid& AssetID);
    
private:
    void LoadAllAssetsFromDisk();
    FAsset LoadAssetFromDisk(const FPath& Path, bool LoadObject = false);
    
    void SaveAllAssetsToDisk();
    void SaveAssetToDisk(FAsset& Asset);
private:
    TMap<FGuid, FAsset> Assets;

};
