// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "Archive.h"

#include "../../Utils/EnumUtils.h"

FArchive::FArchive()  : FArchive(EArchiveType::ART_BINARY){
}


FArchive::FArchive(EArchiveType Type) : ArchiveType(Type){
    if (Type == ART_BINARY) {
            
    }
    else {
        StringArchive = new FStringArchive();
    }
}

FArchive::~FArchive() {
    if (ArchiveType == ART_BINARY) {
            
    }
    else {
        delete StringArchive;
        StringArchive = nullptr;
    }
}

void FArchive::Option(EArchiveAction ArchiveAction) {
    if (ArchiveType == ART_BINARY) {
        
    }
    else {
        StringArchive->Option(ArchiveAction);
    }
}

void FArchive::WriteKey(const std::string& DataKey) {
    StringArchive->WriteKey(DataKey);
}



