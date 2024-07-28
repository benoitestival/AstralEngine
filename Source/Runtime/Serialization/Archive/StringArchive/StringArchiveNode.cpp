#include "StringArchiveNode.h"

#include "../../Utils/TemplateUtils.h"



FStringArchiveNode::FStringArchiveNode() : NodeKey(INVALID_STRING), ParentNode(nullptr), NodeType(ENodeType::NT_NONE){
}

FStringArchiveNode::FStringArchiveNode(FStringArchiveNode* Parent, ENodeType Type) : NodeKey(INVALID_STRING), ParentNode(Parent), NodeType(Type){
}

FStringArchiveNode::~FStringArchiveNode() {
    ParentNode = nullptr;
}

FStringArchiveNode* FStringArchiveNode::GetRootNode() {
    FStringArchiveNode* RootNode = nullptr;
    if (ParentNode != nullptr) {
        RootNode = ParentNode;
        while (RootNode->ParentNode != nullptr) {
            RootNode = RootNode->ParentNode;
        }
    }
    else {
        RootNode = this;
    }
   
    return RootNode;
}

void FStringArchiveNode::StartEditNode() {
    Cast<FStringArchiveRootNode>(GetRootNode())->SetActiveNode(this);
}

void FStringArchiveNode::FinishEditNode() {
    Cast<FStringArchiveRootNode>(GetRootNode())->SetActiveNode(ParentNode);
}

bool FStringArchiveNode::IsActiveNode() {
    return Cast<FStringArchiveRootNode>(GetRootNode())->GetActiveNode() == this;
}

std::string FStringArchiveNode::GetNodeKey() const {
    return NodeKey;
}

void FStringArchiveNode::SetArchiveNodeKey(const std::string& NewNodeKey) {
    NodeKey = NewNodeKey;
}

// EArchiveEntryType FArchiveNode::GetNodeExpectingEntry() const {
//     return ArchiveNodeEntryType;
// }
//
// void FArchiveNode::SetNodeExpectingEntry(EArchiveEntryType NewEntry) {
//     ArchiveNodeEntryType = NewEntry;
// }

ENodeType FStringArchiveNode::GetNodeType() const {
    return NodeType;
}

FStringArchiveNode* FStringArchiveNode::GetParentNode() {
    return ParentNode;
}

FStringArchiveRootNode::FStringArchiveRootNode(){
   ActiveNode = AddSubNode(ENodeType::NT_LEAF);//If no active node is provided we provid our own

}

FStringArchiveRootNode::FStringArchiveRootNode(FStringArchiveNode* NodeActive) : ActiveNode(NodeActive){
}

FStringArchiveRootNode::~FStringArchiveRootNode() {
    ActiveNode = nullptr;
}

FStringArchiveNode* FStringArchiveRootNode::GetActiveNode() {
    return ActiveNode;
}

void FStringArchiveRootNode::SetActiveNode(FStringArchiveNode* NewActiveNode) {
    ActiveNode = NewActiveNode;
}

FStringArchiveParentNode::FStringArchiveParentNode() {
}

FStringArchiveParentNode::FStringArchiveParentNode(FStringArchiveNode* Parent, ENodeType Type) : FStringArchiveNode(Parent, Type), SubNodes({}){
}

FStringArchiveParentNode::~FStringArchiveParentNode() {
    for (auto Node : SubNodes) {
        delete Node;
        Node = nullptr;
    }
    SubNodes.Clear();
}

FStringArchiveNode* FStringArchiveParentNode::AddSubNode(ENodeType NodeType) {
    FStringArchiveNode* NewNode = nullptr;
    if (NodeType == ENodeType::NT_PARENT) {
        NewNode = new FStringArchiveParentNode(this, NodeType);
    }
    else if(NodeType == ENodeType::NT_LEAF) {
        NewNode = new FStringArchiveLeafNode(this, NodeType);
    }
    else {
        //error
    }
    SubNodes.Add(NewNode);
    return NewNode;
}

void FStringArchiveParentNode::RemoveSubNode(FStringArchiveNode* Node) {
    SubNodes.Remove(Node);
    delete Node;
    Node = nullptr;
}

FStringArchiveNode* FStringArchiveParentNode::SwitchSubNodeToType(FStringArchiveNode* Node, ENodeType NewNodeType) {
    FStringArchiveNode* NewNode = nullptr;
    if (Node) {
        if (Node->IsActiveNode()) {
            Node->FinishEditNode();
        }
        std::string NodeKey = Node->GetNodeKey();
        RemoveSubNode(Node);
        NewNode = AddSubNode(NewNodeType);
        NewNode->SetArchiveNodeKey(NodeKey);

        Cast<FStringArchiveRootNode>(GetRootNode())->SetActiveNode(NewNode);
    }
    return NewNode;
}


FStringArchiveLeafNode::FStringArchiveLeafNode() {
}

FStringArchiveLeafNode::FStringArchiveLeafNode(FStringArchiveNode* Parent, ENodeType Type) : FStringArchiveNode(Parent, Type), NodeData(INVALID_STRING){
}

FStringArchiveLeafNode::~FStringArchiveLeafNode() {
}
