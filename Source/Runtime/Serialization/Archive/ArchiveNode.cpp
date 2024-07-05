#include "ArchiveNode.h"

#include "../../Utils/TemplateUtils.h"


FArchiveNodeData::FArchiveNodeData() : DataType(ENodeDataType::NT_RawString), Data(INVALID_STRING){
}

FArchiveNodeData::~FArchiveNodeData() {
    ResetDataType();
}

bool FArchiveNodeData::IsRawString() {
    return DataType == ENodeDataType::NT_RawString;
}

bool FArchiveNodeData::IsNodeArray() {
    return DataType == ENodeDataType::NT_SubNodes;
}

void FArchiveNodeData::InsertRawData(const std::string& RawData) {
    if (!IsRawString()) {
        SwitchToNodeData(ENodeDataType::NT_RawString);
    }
    Data.RawString = Data.RawString + RawData;
}

void FArchiveNodeData::InsertNewNode(FArchiveNode* Node) {
    if (!IsNodeArray()) {
        SwitchToNodeData(ENodeDataType::NT_SubNodes);
    }
    Data.SubNodes.Add(Node);
}

void FArchiveNodeData::RemoveNode(FArchiveNode* Node) {
    if (IsNodeArray()) {
        Data.SubNodes.Remove(Node);
    }
}

void FArchiveNodeData::SwitchToNodeData(ENodeDataType NewDataType) {
    if (NewDataType != DataType) {
        ResetDataType();

        DataType = NewDataType;

        SetupDataType();
    }
}

void FArchiveNodeData::ResetDataType() {
    if (DataType == ENodeDataType::NT_RawString) {
        Data.RawString = "";
    }
    if (DataType == ENodeDataType::NT_SubNodes) {
        for (auto SubNode : Data.SubNodes) {
            delete SubNode;
            SubNode = nullptr;
        }
        Data.SubNodes.Clear();
        Data.SubNodes = {};
    }
}

void FArchiveNodeData::SetupDataType() {
    if (DataType == ENodeDataType::NT_RawString) {
        Data.RawString = "";
    }
    if (DataType == ENodeDataType::NT_SubNodes) {
        Data.SubNodes = {};
    }
}

FArchiveNode::FArchiveNode() : ArchiveNodeEntryType(EArchiveEntryType::AR_INVALID), NodeKey(INVALID_STRING), NodeData(), ParentNode(nullptr){
}

FArchiveNode::FArchiveNode(FArchiveNode* Parent) : ArchiveNodeEntryType(EArchiveEntryType::AR_INVALID), NodeKey(INVALID_STRING), NodeData(), ParentNode(Parent){
}

FArchiveNode::~FArchiveNode() {
    NodeData.ResetDataType();
    ParentNode = nullptr;
}

FArchiveNode* FArchiveNode::AddSubNode() {
    if (NodeData.IsRawString()) {
        NodeData.SwitchToNodeData(ENodeDataType::NT_SubNodes);
    }

    FArchiveNode* NewSubNode = new FArchiveNode(this);
    NodeData.InsertNewNode(NewSubNode);
    
    return NewSubNode;
}

void FArchiveNode::RemoveSubNode(FArchiveNode* Node) {
    if (NodeData.IsNodeArray()) {
        NodeData.RemoveNode(Node);
    }
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

FArchiveRootNode::FArchiveRootNode() : ActiveNode(this){
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
