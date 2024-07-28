#pragma once
#include <string>

#include "StringArchiveNode.h"
#include "../../../Utils/TemplateUtils.h"

class FStringArchive {
public:

    FStringArchive() = default;

    void WriteKey(const std::string& DataKey) {
        ArchiveRootNode->GetActiveNode()->SetArchiveNodeKey(DataKey);
    }
    
    template<class T>
    void WriteData(const T& Data) {
        Cast<FStringArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->InsertDataInNode(Data);
    }

    void Option(EArchiveAction ArchiveAction);

    
private:

    FStringArchiveRootNode* ArchiveRootNode;
};
