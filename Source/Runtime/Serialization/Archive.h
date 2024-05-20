#pragma once
#include <sstream>
#include <string>
#include <unordered_map>

#include "../Utils/Array.h"

#define INVALID_STRING "INVALID"

struct FArchiveNode;

enum class EArchiveEntryType {
    AR_INVALID = 0,
    AR_KEY = 1,
    AR_VALUE = 2,
    AR_START_SUB_ARCHIVE = 3,
    AR_END_SUB_ARCHIVE = 4,
};

enum class EArchiveEntryTypeOption {
    AR_ARRAY_START = 0,
    AR_ARRAY_END = 0,
};

enum class EArchiveFlag {
    AR_NoFlags = 0x00000000,
    AR_Array = 0x00000001,
    //AR_SubArchive = 0x00000002,
};

enum class ENodeDataType {
    NT_RawString = 0,
    NT_SubNode = 1,
};

class EnumUtils {
public:
    
    template<typename EnumType>
    static bool HasFlag(const EnumType Flag, int& Flags){
        return (Flags & Flag) != 0; 
    }

    template<typename EnumType>
    static bool DoesntHasFlag(const EnumType Flag, int& Flags){
        return !HasFlag(Flag, Flags); 
    }

    template<typename EnumType>
    static void AddFlag(const EnumType Flag, int& Flags){
        Flags = Flags | Flag;
    }

    template<typename EnumType>
    static void RemoveFlag(const EnumType Flag, int& Flags){
        Flags = Flags & (~Flag);
    }
};


template <typename T>
concept SupportStringSerialization = requires(std::stringstream& Stream, T value) {
    { Stream << value } -> std::convertible_to<std::ostream&>;
    { Stream >> value } -> std::convertible_to<std::istream&>;
};

struct FStream {
public:
    FStream() = default;
    FStream(const std::string& String) : InternStream(String) {}
    std::string ToString() {
        return InternStream.str();
    }
    std::stringstream& Stream() {
        return InternStream;
    }
private:
    std::stringstream InternStream;
};

struct FArchiveNodeData {

    FArchiveNodeData() : DataType(ENodeDataType::NT_RawString), String(INVALID_STRING), Node(nullptr) {
    }
private:
    ENodeDataType DataType;
    union {
        std::string String;
        FArchiveNode* Node;
    };
};

struct FArchiveNode {
public:
    FArchiveNode() : ArchiveNodeEntryType(EArchiveEntryType::AR_INVALID), NodeKey(INVALID_STRING), NodeData(), ParentNode(nullptr){
    }

    FArchiveNode* AddSubNode() {
        return nullptr;
    }
    void RemoveSubNode() {
        
    }
    FArchiveNode* GetRootNode() {
        return nullptr;
    }
    void FinishEditNode() {
        
    }
    
    template<class T>
    void InsertData(T& Data) {
        if (ArchiveNodeEntryType == EArchiveEntryType::AR_KEY) {
            //TODO 
        }
        if(ArchiveNodeEntryType == EArchiveEntryType::AR_VALUE) {
            //TODO 
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
    FArchiveRootNode() : ActiveNode(nullptr){
    }

    FArchiveNode* GetActiveNode() {
        return ActiveNode;
    }
    void SetActiveNode(FArchiveNode* NewActiveNode) {
        ActiveNode = NewActiveNode;
    }
private:
    FArchiveNode* ActiveNode;
};

struct FArchive {
public:
    
    FArchive() : ArchiveFlags(0), ArchiveRootNode(nullptr){
    }
    
    FArchive& operator<<(EArchiveEntryType& EntryType) {
        if (IsBasicEntry(EntryType)) {
            ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EntryType;
        }
        else if (EntryType == EArchiveEntryType::AR_START_SUB_ARCHIVE) {
            ArchiveRootNode->GetActiveNode()->AddSubNode();
        }
        else if (EntryType == EArchiveEntryType::AR_END_SUB_ARCHIVE) {
            ArchiveRootNode->GetActiveNode()->FinishEditNode();
        }
        return *this;
    }
    FArchive& operator<<(EArchiveEntryTypeOption& EntryTypeOption) {
        if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_START) {
            EnumUtils::AddFlag(EArchiveFlag::AR_Array, ArchiveFlags);
        }
        if (EntryTypeOption == EArchiveEntryTypeOption::AR_ARRAY_END) {
            EnumUtils::RemoveFlag(EArchiveFlag::AR_Array, ArchiveFlags);
        }
        return *this;
    }
    template<SupportStringSerialization T>
    FArchive& operator<<(T& Value) {
        if (ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType != EArchiveEntryType::AR_INVALID) {
            ArchiveRootNode->GetActiveNode()->InsertData(Value);
            ArchiveRootNode->GetActiveNode()->ArchiveNodeEntryType = EArchiveEntryType::AR_INVALID;//Clear the archive
        }
        else {
            //output error
        }
        return *this;
    }

    // template<SupportStringSerialization T>
    // FArchive& operator>>(T& Value) {
    //     DataStream.Stream() >> Value;
    //     return *this;
    // }
    // template<class T>
    // T DataFromString(std::string& FieldValue) {
    //     T Data = T();
    //     *this >> Data;
    //     return Data;
    // }
private:
    bool IsBasicEntry(EArchiveEntryType EntryType) {
        return EntryType == EArchiveEntryType::AR_KEY || EntryType == EArchiveEntryType::AR_VALUE;
    }
private:
    int ArchiveFlags;
    FArchiveRootNode* ArchiveRootNode;
};



