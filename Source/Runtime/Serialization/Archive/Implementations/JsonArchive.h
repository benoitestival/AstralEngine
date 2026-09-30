#pragma once
#include <fstream>

#include "../Archive.h"
#include "nlohmann/json.hpp"

using JsonObject = nlohmann::json;

class JsonArchive : public FArchive {
public:
    using FArchive::Serialize;
    using FArchive::DeSerialize;
    
    JsonArchive(bool IsLoadingArchive, EChecksumType ArChecksumType);
    
    virtual void SerializeChecksum(TArray<char>& Checksum) override;
    virtual TArray<char> DeserializeChecksum() override;
private:
    char ConvertDecimalToHex(char Num);
    char ConvertHexToDecimal(char Num);
public:
    virtual TArray<char> GetArchiveRawDatas() override;
    virtual void SetArchiveRawDatas(TArray<char>& RawDatas) override;
    
    virtual void Serialize(const std::string& Key, bool& Data) override;
    virtual void Serialize(const std::string& Key, int& Data) override;
    virtual void Serialize(const std::string& Key, float& Data) override;
    virtual void Serialize(const std::string& Key, std::string& Data) override;

    virtual void DeSerialize(const std::string& Key, bool& Data) override;
    virtual void DeSerialize(const std::string& Key, int& Data) override;
    virtual void DeSerialize(const std::string& Key, float& Data) override;
    virtual void DeSerialize(const std::string& Key, std::string& Data) override;

    //Nodes Function
    virtual void BeginSubNode(const std::string& NodeName) override;
    virtual void EndSubNode(const std::string& NodeName) override;

    //Containers Functions
    virtual void BeginContainer(const std::string& NodeName, int& Size) override;
    virtual void EndContainer(const std::string& NodeName) override;

    virtual void BeginAnonymousElement() override;
    virtual void EndAnonymousElement() override;

    virtual bool IsReading() override;
    
private:
    JsonObject& GetCurrentNode();

    template<class T>
    void ReadData(const std::string& NodeName, T& Data) {
        if (!NodeName.empty()) {
            Data = GetCurrentNode().at(NodeName).get<T>();
        }
        else {
            Data = GetCurrentNode().get<T>();
        }
    };

    template<class T>
    void WriteData(const std::string& NodeName, T& Data) {
        if (!NodeName.empty()) {
            GetCurrentNode()[NodeName] = Data;
        }
        else {
            GetCurrentNode() = Data;
        }
    }
    
private:
    JsonObject RootNode;
    TArray<JsonObject*> ArchiveNodes;

    //We have this stack to go threw a list of anonymous eleents, it s a TArray in case we have an array in an array
    TArray<JsonObject::iterator> AnonymousReadIteratorStack;//Only used in read

    bool IsLoadingArchiveType;
};
