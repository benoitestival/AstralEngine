#pragma once
#include "../Utils/SerializationUtils.h"
#include "StringArchive/StringArchive.h"

#define ARRAY_SEPARATOR ","

class FArchive {
public:
    FArchive();
    FArchive(EArchiveType Type);
    ~FArchive();

    template<class T>
    void WriteData(const std::string& DataKey, const T& Data) {
        WriteKey(DataKey);
        *this << Data;
    };

    template<class T>
    void ReadData(const std::string& DataKey, T& Data) {
        ReadKey(DataKey);
        *this >> Data;
    };
    
    template<SupportStringSerialization T>
    FArchive& operator<<(const T& Value) {
        if (ArchiveType == ART_BINARY) {
            
        }
        else {
            StringArchive->WriteData(Value);
        }
        return *this;
    }

    template<SupportStringSerialization T>
    FArchive& operator>>(const T& Value) {
        if (ArchiveType == ART_BINARY) {
            
        }
        else {
            StringArchive->ReadData(Value);
        }
        return *this;
    }

    void Option(EArchiveAction ArchiveAction);
    
private:
    void WriteKey(const std::string& DataKey);
    void ReadKey(const std::string& DataKey);

private:
    EArchiveType ArchiveType;
    union {
        FStringArchive* StringArchive;
    };
};
