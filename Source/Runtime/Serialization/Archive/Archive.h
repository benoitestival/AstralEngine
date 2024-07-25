#pragma once
#include "ArchiveNode.h"
#include "../../Utils/EnumUtils.h"
#include "../Utils/SerializationUtils.h"

#define ARRAY_SEPARATOR ","

class FArchive {
public:
    FArchive();
    
    FArchive& operator<<(const EArchiveEntryType& EntryType);
    template<SupportStringSerialization T>
    FArchive& operator<<(const T& Value) {
        if (ArchiveEntryType != EArchiveEntryType::AR_INVALID) {
            if (ArchiveEntryType == EArchiveEntryType::AR_KEY) {
                ArchiveRootNode->GetActiveNode()->SetArchiveNodeKey(Value);
            }
            else if(ArchiveEntryType == EArchiveEntryType::AR_VALUE) {
                if (ArchiveRootNode->GetActiveNode()->GetNodeType() == ENodeType::NT_LEAF) {
                    Cast<FArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->InsertDataInNode(Value);
                }
            }
            ArchiveEntryType = EArchiveEntryType::AR_INVALID;//Clear the archive entry type

        }
        else {
            //output error
        }
        return *this;
    }

    FArchive& operator>>(const EArchiveEntryType& EntryType);
    template<SupportStringSerialization T>
    FArchive& operator>>(const T& Value) {
        if (ArchiveEntryType != EArchiveEntryType::AR_INVALID) {
            if (ArchiveEntryType == EArchiveEntryType::AR_KEY) {
                
            }
            else if(ArchiveEntryType == EArchiveEntryType::AR_VALUE) {
                
            }
            ArchiveEntryType = EArchiveEntryType::AR_INVALID;
        }
        return *this;
    }

    std::string ToString();
private:
    bool IsBasicEntry(EArchiveEntryType EntryType) {
        return EntryType == EArchiveEntryType::AR_KEY || EntryType == EArchiveEntryType::AR_VALUE;
    }
private:
    int ArchiveFlags;
    FArchiveRootNode* ArchiveRootNode;

    EArchiveEntryType ArchiveEntryType;

};
