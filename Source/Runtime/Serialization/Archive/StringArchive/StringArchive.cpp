#include "StringArchive.h"
//
// void FStringArchive::WriteKey(const std::string& DataKey){
//     ArchiveRootNode->GetActiveNode()->SetArchiveNodeKey(DataKey);
// }
//
// void FStringArchive::ReadKey(const std::string& DataKey) {
//     //ArchiveRootNode->GetActiveNode()
//     
// }

void FStringArchive::Option(EArchiveAction ArchiveAction) {
    //TODO Need Redo to work with Read functions
    // if (ArchiveAction == EArchiveAction::AR_ENTER_SUB_ARCHIVE) {
    //     FStringArchiveParentNode* ActiveNode = nullptr;
    //     if (ArchiveRootNode->GetActiveNode()->GetNodeType() == ENodeType::NT_LEAF) {
    //         FStringArchiveParentNode* ActiveNodeParent = Cast<FStringArchiveParentNode>(ArchiveRootNode->GetActiveNode()->GetParentNode());
    //         ActiveNode = Cast<FStringArchiveParentNode>(ActiveNodeParent->SwitchSubNodeToType(ArchiveRootNode->GetActiveNode(), ENodeType::NT_PARENT));
    //     }
    //     else {
    //         ActiveNode = Cast<FStringArchiveParentNode>(ArchiveRootNode->GetActiveNode());
    //     }
    //     FStringArchiveNode* NewNode = ActiveNode->AddSubNode(ENodeType::NT_LEAF);
    //     NewNode->StartEditNode();
    // }
    // if (ArchiveAction == EArchiveAction::AR_EXIT_SUB_ARCHIVE) {
    //     ArchiveRootNode->GetActiveNode()->FinishEditNode();
    // }
}
