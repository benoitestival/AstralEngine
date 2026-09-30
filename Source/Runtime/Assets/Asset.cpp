#include "Asset.h"

#include "../Serialization/Archive/Implementations/JsonArchive.h"

ABaseObject* FAsset::GetOrLoad() {
    if (AssetLoadedObject == nullptr) {
        JsonArchive ObjectArchive = JsonArchive(true, EChecksumType::ECT_CRC32);
        ObjectArchive.LoadFromFile(AssetPath);
        ObjectArchive.DeSerialize("AssetObject", AssetLoadedObject);
    }
    return AssetLoadedObject;
}
