// #pragma once
// #include <string>
//
// //#include "StringArchiveNode.h"
// #include <unordered_map>
//
// #include "../../../Utils/Map.h"
// #include "../../../Utils/TemplateUtils.h"
// #include "../../Utils/SerializationUtils.h"
//
// class FStringArchive {
// public:
//
//     FStringArchive() = default;
//     
//     template<SupportStringSerialization T>
//     void WriteField(const std::string& DataKey, );
//
//     template<SupportStringSerialization T>
//     void ReadField(const std::string& DataKey, );
//     
//     // template<class T>
//     // void WriteData(const T& Data) {
//     //     Cast<FStringArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->InsertDataInNode(Data);
//     // }
//     //
//     // template<class T>
//     // void ReadData(const T& Data) {
//     //     Cast<FStringArchiveLeafNode>(ArchiveRootNode->GetActiveNode())->ReadDataInNode(Data);
//     // }
//
//     void Option(EArchiveAction ArchiveAction);
//
//     
// private:
//
//     //FStringArchiveRootNode* ArchiveRootNode;
// };
//
//
