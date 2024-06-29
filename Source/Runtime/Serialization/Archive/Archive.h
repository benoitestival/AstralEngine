#pragma once
#include "ArchiveNode.h"
#include "../../Utils/EnumUtils.h"
#include "../Utils/SerializationUtils.h"

#define ARRAY_SEPARATOR ","

class FArchive {
public:
    FArchive();
    
    FArchive& operator<<(const EArchiveEntryType& EntryType);
    FArchive& operator<<(const EArchiveEntryTypeOption& EntryTypeOption);
    template<SupportStringSerialization T>
    FArchive& operator<<(const T& Value) {
        if (ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType != EArchiveEntryType::AR_INVALID) {
            if (ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType == EArchiveEntryType::AR_KEY) {
                ArchiveRootNode->GetActiveNode()->InsertData(Value);
                ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;//Clear the archive entry type
            }
            else if(ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType == EArchiveEntryType::AR_VALUE) {
                if (EnumUtils::HasFlag(EArchiveFlag::AR_Array,ArchiveFlags)) {
                    ArchiveRootNode->GetActiveNode()->InsertData(Value);
                    ArchiveRootNode->GetActiveNode()->InsertData(ARRAY_SEPARATOR);
                }
                else {
                    ArchiveRootNode->GetActiveNode()->InsertData(Value);
                    ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;//Clear the archive entry type
                }
            }
            
        }
        else {
            //output error
        }
        return *this;
    }

    //TODO In (>>) operator
private:
    bool IsBasicEntry(EArchiveEntryType EntryType) {
        return EntryType == EArchiveEntryType::AR_KEY || EntryType == EArchiveEntryType::AR_VALUE;
    }
private:
    int ArchiveFlags;
    FArchiveRootNode* ArchiveRootNode;
};
