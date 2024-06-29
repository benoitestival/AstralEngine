#pragma once

#include "../../Utils/Array.h"
#include "../Utils/SerializationUtils.h"

struct FArchiveNode;

struct FArchiveNodeData {

    FArchiveNodeData();
    ~FArchiveNodeData();
    
    bool IsRawString();
    bool IsNodeArray();

    void InsertRawData(const std::string& Data);
    
    void InsertNewNode(FArchiveNode* Node);
    void RemoveNode(FArchiveNode* Node);
    
    void SwitchToNodeData(ENodeDataType NewDataType);
    
    void ResetDataType();
    void SetupDataType();
private:
    ENodeDataType DataType;
    union {
        std::string String;
        TArray<FArchiveNode*> Nodes;
    };
};

struct FArchiveNode {
public:
    FArchiveNode();
    FArchiveNode(FArchiveNode* Parent);
    ~FArchiveNode();

    FArchiveNode* AddSubNode();
    void RemoveSubNode(FArchiveNode* Node);
    FArchiveNode* GetRootNode();

    void StartEditNode();
    void FinishEditNode();

    bool IsActiveNode();
    
    template<class T>
    void InsertData(T& Data) {
        FStream Stream = FStream();
        Stream.Stream() << Data;
        if (ArchiveNodeEntryType == EArchiveEntryType::AR_KEY) {
            NodeKey = Stream.ToString();
        }
        if(ArchiveNodeEntryType == EArchiveEntryType::AR_VALUE) {
            if (NodeData.IsRawString()) {
                NodeData.InsertRawData(Stream.ToString());
            }
            else {
                //output error
            }
        }
    }
public:
    EArchiveEntryType ArchiveNodeEntryType;
    
    std::string NodeKey;
    FArchiveNodeData NodeData;

private:
    FArchiveNode* ParentNode;
};

struct FArchiveRootNode : FArchiveNode{
public:
    FArchiveRootNode();
    FArchiveRootNode(FArchiveNode* NodeActive);
    ~FArchiveRootNode();
    FArchiveNode* GetActiveNode();
    void SetActiveNode(FArchiveNode* NewActiveNode);
private:
    FArchiveNode* ActiveNode;
};
