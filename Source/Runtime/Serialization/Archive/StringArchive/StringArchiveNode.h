#pragma once

#include "../../../Utils/Array.h"
#include "../../Utils/SerializationUtils.h"


struct FStringArchiveNode {
public:
    FStringArchiveNode();
    FStringArchiveNode(FStringArchiveNode* Parent, ENodeType Type);
    virtual ~FStringArchiveNode();
    
    void StartEditNode();
    void FinishEditNode();

    FStringArchiveNode* GetRootNode();
    bool IsActiveNode();

    std::string GetNodeKey() const;
    void SetArchiveNodeKey(const std::string& NewNodeKey);

    // EArchiveEntryType GetNodeExpectingEntry() const;
    // void SetNodeExpectingEntry(EArchiveEntryType NewEntry);

    ENodeType GetNodeType() const;
    FStringArchiveNode* GetParentNode();;
private:
    std::string NodeKey;
    //EArchiveEntryType ArchiveNodeEntryType;

    FStringArchiveNode* ParentNode;
    ENodeType NodeType;
};

struct FStringArchiveParentNode : FStringArchiveNode {
public:
    FStringArchiveParentNode();
    FStringArchiveParentNode(FStringArchiveNode* Parent, ENodeType Type);
    virtual ~FStringArchiveParentNode();
    
    FStringArchiveNode* AddSubNode(ENodeType NodeType);
    void RemoveSubNode(FStringArchiveNode* Node);

    FStringArchiveNode* SwitchSubNodeToType(FStringArchiveNode* Node, ENodeType NewNodeType);
private:
    TArray<FStringArchiveNode*> SubNodes;
};

struct FStringArchiveRootNode : FStringArchiveParentNode{
public:
    FStringArchiveRootNode();
    FStringArchiveRootNode(FStringArchiveNode* NodeActive);
    virtual ~FStringArchiveRootNode();
    FStringArchiveNode* GetActiveNode();
    void SetActiveNode(FStringArchiveNode* NewActiveNode);
private:
    FStringArchiveNode* ActiveNode;
};

struct FStringArchiveLeafNode : FStringArchiveNode {
public:
    FStringArchiveLeafNode();
    FStringArchiveLeafNode(FStringArchiveNode* Parent, ENodeType Type);
    virtual ~FStringArchiveLeafNode();

    template<class T>
    void InsertDataInNode(T& Data) {
        FStream Stream = FStream();
        Stream.Stream() << Data;
        NodeData = Stream.ToString();
    }

    template<class T>
    void ReadDataInNode(T& Data) {
        // FStream Stream = FStream();
        // Stream.Stream() << NodeData;
        // Data = Stream.Stream();
    }
private:
    std::string NodeData;
};
