#pragma once

#include "../../Utils/Array.h"
#include "../Utils/SerializationUtils.h"



struct FArchiveNode {
public:
    FArchiveNode();
    FArchiveNode(FArchiveNode* Parent, ENodeType Type);
    virtual ~FArchiveNode();
    
    void StartEditNode();
    void FinishEditNode();

    FArchiveNode* GetRootNode();
    bool IsActiveNode();

    std::string GetNodeKey() const;
    void SetArchiveNodeKey(const std::string& NewNodeKey);

    // EArchiveEntryType GetNodeExpectingEntry() const;
    // void SetNodeExpectingEntry(EArchiveEntryType NewEntry);

    ENodeType GetNodeType() const;
    FArchiveNode* GetParentNode();;
private:
    std::string NodeKey;
    //EArchiveEntryType ArchiveNodeEntryType;

    FArchiveNode* ParentNode;
    ENodeType NodeType;
};

struct FArchiveParentNode : FArchiveNode {
public:
    FArchiveParentNode();
    FArchiveParentNode(FArchiveNode* Parent, ENodeType Type);
    virtual ~FArchiveParentNode();
    
    FArchiveNode* AddSubNode(ENodeType NodeType);
    void RemoveSubNode(FArchiveNode* Node);

    FArchiveNode* SwitchSubNodeToType(FArchiveNode* Node, ENodeType NewNodeType);
private:
    TArray<FArchiveNode*> SubNodes;
};

struct FArchiveRootNode : FArchiveParentNode{
public:
    FArchiveRootNode();
    FArchiveRootNode(FArchiveNode* NodeActive);
    virtual ~FArchiveRootNode();
    FArchiveNode* GetActiveNode();
    void SetActiveNode(FArchiveNode* NewActiveNode);
private:
    FArchiveNode* ActiveNode;
};

struct FArchiveLeafNode : FArchiveNode {
public:
    FArchiveLeafNode();
    FArchiveLeafNode(FArchiveNode* Parent, ENodeType Type);
    virtual ~FArchiveLeafNode();

    template<class T>
    void InsertDataInNode(T& Data) {
        FStream Stream = FStream();
        Stream.Stream() << Data;
        NodeData = Stream.ToString();
    }
private:
    std::string NodeData;
};
