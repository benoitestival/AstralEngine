#include "ArchiveNode.h"

#include "../../Utils/TemplateUtils.h"



FArchiveNode::FArchiveNode() : NodeKey(INVALID_STRING), ArchiveNodeEntryType(EArchiveEntryType::AR_INVALID), ParentNode(nullptr), NodeType(ENodeType::NT_NONE){
}

FArchiveNode::FArchiveNode(FArchiveNode* Parent, ENodeType Type) : NodeKey(INVALID_STRING), ArchiveNodeEntryType(EArchiveEntryType::AR_INVALID), ParentNode(Parent), NodeType(Type){
}

FArchiveNode::~FArchiveNode() {
    ParentNode = nullptr;
}

FArchiveNode* FArchiveNode::GetRootNode() {
    FArchiveNode* RootNode = ParentNode;
    while (RootNode->ParentNode != nullptr) {
        RootNode = RootNode->ParentNode;
    }
    return RootNode;
}

void FArchiveNode::StartEditNode() {
    Cast<FArchiveRootNode>(GetRootNode())->SetActiveNode(this);
    ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;
}

void FArchiveNode::FinishEditNode() {
    ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;
    Cast<FArchiveRootNode>(GetRootNode())->SetActiveNode(ParentNode);
}

bool FArchiveNode::IsActiveNode() {
    return Cast<FArchiveRootNode>(GetRootNode())->GetActiveNode() == this;
}

std::string FArchiveNode::GetNodeKey() const {
    return NodeKey;
}

void FArchiveNode::SetArchiveNodeKey(const std::string& NewNodeKey) {
    NodeKey = NewNodeKey;
}

EArchiveEntryType FArchiveNode::GetNodeExpectingEntry() const {
    return ArchiveNodeEntryType;
}

void FArchiveNode::SetNodeExpectingEntry(EArchiveEntryType NewEntry) {
    ArchiveNodeEntryType = NewEntry;
}

ENodeType FArchiveNode::GetNodeType() const {
    return NodeType;
}

FArchiveNode* FArchiveNode::GetParentNode() {
    return ParentNode;
}

FArchiveRootNode::FArchiveRootNode(){
   ActiveNode = AddSubNode(ENodeType::NT_LEAF);//If no active node is provided we provid our own

}

FArchiveRootNode::FArchiveRootNode(FArchiveNode* NodeActive) : ActiveNode(NodeActive){
}

FArchiveRootNode::~FArchiveRootNode() {
    ActiveNode = nullptr;
}

FArchiveNode* FArchiveRootNode::GetActiveNode() {
    return ActiveNode;
}

void FArchiveRootNode::SetActiveNode(FArchiveNode* NewActiveNode) {
    ActiveNode = NewActiveNode;
}

FArchiveParentNode::FArchiveParentNode() {
}

FArchiveParentNode::FArchiveParentNode(FArchiveNode* Parent, ENodeType Type) : FArchiveNode(Parent, Type), SubNodes({}){
}

FArchiveParentNode::~FArchiveParentNode() {
    for (auto Node : SubNodes) {
        delete Node;
        Node = nullptr;
    }
    SubNodes.Clear();
}

FArchiveNode* FArchiveParentNode::AddSubNode(ENodeType NodeType) {
    FArchiveNode* NewNode = nullptr;
    if (NodeType == ENodeType::NT_PARENT) {
        NewNode = new FArchiveParentNode(this, NodeType);
    }
    else if(NodeType == ENodeType::NT_LEAF) {
        NewNode = new FArchiveLeafNode(this, NodeType);
    }
    else {
        //error
    }
    SubNodes.Add(NewNode);
    return NewNode;
}

void FArchiveParentNode::RemoveSubNode(FArchiveNode* Node) {
    SubNodes.Remove(Node);
    delete Node;
    Node = nullptr;
}

FArchiveNode* FArchiveParentNode::SwitchSubNodeToType(FArchiveNode* Node, ENodeType NewNodeType) {
    FArchiveNode* NewNode = nullptr;
    if (Node) {
        if (Node->IsActiveNode()) {
            Node->FinishEditNode();
        }
        std::string NodeKey = Node->GetNodeKey();
        RemoveSubNode(Node);
        NewNode = AddSubNode(NewNodeType);
        NewNode->SetArchiveNodeKey(NodeKey);

        Cast<FArchiveRootNode>(GetRootNode())->SetActiveNode(NewNode);
    }
    return NewNode;
}


FArchiveLeafNode::FArchiveLeafNode() {
}

FArchiveLeafNode::FArchiveLeafNode(FArchiveNode* Parent, ENodeType Type) {
}

FArchiveLeafNode::~FArchiveLeafNode() {
}
