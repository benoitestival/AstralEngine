#pragma once
#include <string>

#include "StringArchiveNode.h"
#include <unordered_map>

#include "../../../Utils/TemplateUtils.h"

class FStringArchive {
public:

    FStringArchive() = default;

    void WriteKey(const std::string& DataKey);
    void ReadKey(const std::string& DataKey);
    
    template<class T>
    void WriteData(const T& Data) {
        Cast<FStringArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->InsertDataInNode(Data);
    }

    template<class T>
    void ReadData(const T& Data) {
        Cast<FStringArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->ReadDataInNode(Data);
    }

    void Option(EArchiveAction ArchiveAction);

    
private:

    FStringArchiveRootNode* ArchiveRootNode;
};


// class FStringArchiveNode {
//     std::unordered_map<int, std::string> test = {{}};
// };