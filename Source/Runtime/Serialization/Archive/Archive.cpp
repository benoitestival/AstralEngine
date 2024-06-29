#include "Archive.h"

#include "../../Utils/EnumUtils.h"

FArchive::FArchive() : ArchiveFlags(0){
    ArchiveRootNode = new FArchiveRootNode();
}

FArchive& FArchive::operator<<(const EArchiveEntryType& EntryType) {
    if (IsBasicEntry(EntryType)) {
        ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EntryType;
    }
    else if (EntryType == EArchiveEntryType::AR_START_SUB_ARCHIVE) {
        FArchiveNode* NewNode = ArchiveRootNode->GetActiveNode()->AddSubNode();
        NewNode->StartEditNode();
    }
    else if (EntryType == EArchiveEntryType::AR_END_SUB_ARCHIVE) {
        ArchiveRootNode->GetActiveNode()->FinishEditNode();
    }
    return *this;
}

FArchive& FArchive::operator<<(const EArchiveEntryTypeOption& EntryTypeOption) {
    if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_START) {
        EnumUtils::AddFlag(EArchiveFlag::AR_Array, ArchiveFlags);
    }
    if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_END) {
        EnumUtils::RemoveFlag(EArchiveFlag::AR_Array, ArchiveFlags);
    }
    return *this;
}
