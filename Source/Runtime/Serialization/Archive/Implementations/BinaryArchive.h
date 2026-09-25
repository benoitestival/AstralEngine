#pragma once
#include "../Archive.h"
#include <filesystem>

class BinaryArchive : public FArchive {
public:
    using FArchive::Serialize;
    using FArchive::DeSerialize;

    BinaryArchive(bool IsLoadingArchive);

    virtual bool LoadFromFile(const std::string& Path) override;
    virtual void SaveToFile(const std::string& Path) override;
    
    virtual void Serialize(const std::string& Key, bool& Data) override;
    virtual void Serialize(const std::string& Key, int& Data) override;
    virtual void Serialize(const std::string& Key, float& Data) override;
    virtual void Serialize(const std::string& Key, std::string& Data) override;

    virtual void DeSerialize(const std::string& Key, bool& Data) override;
    virtual void DeSerialize(const std::string& Key, int& Data) override;
    virtual void DeSerialize(const std::string& Key, float& Data) override;
    virtual void DeSerialize(const std::string& Key, std::string& Data) override;

    virtual void BeginContainer(const std::string& NodeName, int& Size) override;
    
    virtual bool IsReading() override;

private:
    virtual void SerializeRaw(char* Data, int Size);
    virtual void DeSerializeRaw(char* Data, int Size);
    
private:
    TArray<char> Buffer;
    bool IsReadingArchive;
    int ReadOffset;
};
