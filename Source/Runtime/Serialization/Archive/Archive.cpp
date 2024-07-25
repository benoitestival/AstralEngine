// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "Archive.h"

#include "../../Utils/EnumUtils.h"

FArchive::FArchive() : ArchiveFlags(0), ArchiveEntryType(EArchiveEntryType::AR_INVALID){
    ArchiveRootNode = new FArchiveRootNode();
}

FArchive& FArchive::operator<<(const EArchiveEntryType& EntryType) {
    if (IsBasicEntry(EntryType)) {
        if (EntryType == EArchiveEntryType::AR_KEY && ArchiveRootNode->GetActiveNode()->GetNodeKey() != INVALID_STRING) {//Its a Key so we should create a new node
            FArchiveNode* NewNode = Cast<FArchiveParentNode>(ArchiveRootNode->GetActiveNode()->GetParentNode())->AddSubNode(ENodeType::NT_LEAF);
            NewNode->StartEditNode();
        }
        ArchiveEntryType = EntryType;
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
        ArchiveEntryType = EArchiveEntryType::AR_INVALID;
    }
    else if (EntryType == EArchiveEntryType::AR_END_SUB_ARCHIVE) {
        ArchiveRootNode->GetActiveNode()->FinishEditNode();
        ArchiveEntryType = EArchiveEntryType::AR_INVALID;
    }
    return *this;
}

FArchive& FArchive::operator>>(const EArchiveEntryType& EntryType) {
    
    return *this;
}

std::string FArchive::ToString() {
    std::string ArchiveAsString = "";
    
    return ArchiveAsString;
}
