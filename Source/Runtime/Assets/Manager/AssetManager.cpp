#include "AssetManager.h"

#include "../../Serialization/Archive/Implementations/JsonArchive.h"
#include "../../Utils/Path/Path.h"


void AAssetManager::Init() {
    Super::Init();
    LoadAllAssetsFromDisk();
}

void AAssetManager::DeInit() {
    SaveAllAssetsToDisk();
    Super::DeInit();
}

FAsset AAssetManager::GetAssetFromID(const FGuid& AssetID) {
    return Assets.Find(AssetID);
}

ABaseObject* AAssetManager::LoadObjectFromID(const FGuid& AssetID) {
    return Assets.Find(AssetID).GetOrLoad();
}

void AAssetManager::LoadAllAssetsFromDisk() {
    FPath ContentPath = FPathUtils::GetEngineContentPath();
    for (const FPath& Path : FPathIterator(ContentPath)) {
        if (Path.HasExtension(FPathExtension("meta"))) {
            FAsset Asset = LoadAssetFromDisk(Path.RemoveExtension());
            Assets.Insert(Asset.AssetID, Asset);
        }
    }
}

FAsset AAssetManager::LoadAssetFromDisk(const FPath& Path, bool LoadObject) {
    FAsset Asset = FAsset();
    
    FPath AssetMetaDataPath = Path + FPathExtension("meta");
    std::ifstream Stream = std::ifstream(AssetMetaDataPath.ToString(), std::ifstream::binary);
    if (Stream.is_open()) {
        
        //Construct the archive that load the meta datas
        JsonArchive MetaDataArchive = JsonArchive(true, EChecksumType::ECT_CRC32);
        MetaDataArchive.LoadFromFile(AssetMetaDataPath, Stream);

        FGuid AssetID = FGuid();
        MetaDataArchive.DeSerialize("AssetID", AssetID);
        
        std::string AssetClassName = std::string();
        MetaDataArchive.DeSerialize("AssetClass", AssetClassName);

        if (AstralEngineStatics::IsClassRegister(AssetClassName)) {
            Asset.AssetPath = Path;
            Asset.AssetID = AssetID;
            Asset.AssetClass = AstralEngineStatics::GetClass(AssetClassName);

            if (LoadObject) {
                //Construct the Archive for the object
                JsonArchive ObjectArchive = JsonArchive(true, EChecksumType::ECT_CRC32);
                ObjectArchive.LoadFromFile(Path);
                ObjectArchive.DeSerialize("AssetObject", Asset.AssetLoadedObject);
            }
        }
    }
    return Asset;
}

void AAssetManager::SaveAllAssetsToDisk() {
    for (auto& Asset : Assets) {
        SaveAssetToDisk(Asset.second);
    }
}

void AAssetManager::SaveAssetToDisk(FAsset& Asset) {
    std::ofstream Stream = std::ofstream((Asset.AssetPath + FPathExtension("meta")).ToString(), std::ofstream::binary);
    if (Stream.is_open()) {
        //Construct the archive that write the meta datas
        JsonArchive MetaDataArchive = JsonArchive(false, EChecksumType::ECT_CRC32);

        MetaDataArchive.Serialize("AssetID", Asset.AssetID);
        
        std::string AssetClassName = Asset.AssetClass->GetClassName();
        MetaDataArchive.Serialize("AssetClass", AssetClassName);
        
        MetaDataArchive.SaveToFile(Asset.AssetPath + FPathExtension("meta"), Stream);

        if (Asset.AssetLoadedObject != nullptr) {
            //Construct the Archive for the object
            JsonArchive ObjectArchive = JsonArchive(false, EChecksumType::ECT_CRC32);
            ObjectArchive.Serialize("AssetObject", Asset.AssetLoadedObject);
            ObjectArchive.SaveToFile(Asset.AssetPath);
        }
    }
}
