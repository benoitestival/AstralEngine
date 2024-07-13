// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "Archive.h"

#include "../../Utils/EnumUtils.h"

FArchive::FArchive() : ArchiveFlags(0){
    ArchiveRootNode = new FArchiveRootNode();
}

FArchive& FArchive::operator<<(const EArchiveEntryType& EntryType) {
    if (IsBasicEntry(EntryType)) {
        ArchiveRootNode->GetActiveNode()->SetNodeExpectingEntry(EntryType);
    }
    else if (EntryType == EArchiveEntryType::AR_START_SUB_ARCHIVE) {
        FArchiveParentNode* ActiveNode = nullptr;
        if (ArchiveRootNode->GetActiveNode()->GetNodeType() == ENodeType::NT_LEAF) {
            FArchiveParentNode* ActiveNodeParent = Cast<FArchiveParentNode>(ArchiveRootNode->GetActiveNode()->GetParentNode());
            ActiveNode = Cast<FArchiveParentNode>(ActiveNodeParent->SwitchSubNodeToType(ArchiveRootNode->GetActiveNode(), ENodeType::NT_PARENT));
        }
        else {
            ActiveNode = Cast<FArchiveParentNode>(ArchiveRootNode->GetActiveNode());
        }
        
        FArchiveNode* NewNode = ActiveNode->AddSubNode(ENodeType::NT_LEAF);
        
        NewNode->StartEditNode();
    }
    else if (EntryType == EArchiveEntryType::AR_END_SUB_ARCHIVE) {
        ArchiveRootNode->GetActiveNode()->FinishEditNode();
    }
    return *this;
}

// FArchive& FArchive::operator<<(const EArchiveEntryTypeOption& EntryTypeOption) {
//     if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_START) {
//         EnumUtils::AddFlag(EArchiveFlag::AR_Array, ArchiveFlags);
//     }
//     if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_END) {
//         EnumUtils::RemoveFlag(EArchiveFlag::AR_Array, ArchiveFlags);
//     }
//     return *this;
// }
