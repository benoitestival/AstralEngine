#pragma once
#include "ArchiveNode.h"
#include "../Utils/SerializationUtils.h"

class FArchive {
public:
    FArchive();
    
    FArchive& operator<<(EArchiveEntryType& EntryType);
    FArchive& operator<<(EArchiveEntryTypeOption& EntryTypeOption);
    template<SupportStringSerialization T>
    FArchive& operator<<(T& Value) {
        if (ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType != EArchiveEntryType::AR_INVALID) {
            ArchiveRootNode->GetActiveNode()->InsertData(Value);
            // if () {
            //     
            // }
            ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;//Clear the archive entry type
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
