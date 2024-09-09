#pragma once
#include "../../Utils/Map.h"
#include "../Utils/SerializationUtils.h"

#define ARRAY_SEPARATOR ","

template<class T>
class TSerializableField {
public:
    TSerializableField() {
        DataKey = INVALID_STRING;
        Data = nullptr;
    }
    TSerializableField(const std::string& Key, T& FieldData) {
        DataKey = Key;
        Data = &FieldData;
    }
    TSerializableField(const std::string& Key, T* FieldData) {
        DataKey = Key;
        Data = FieldData;
    }

    std::string Key() const {
        return DataKey;
    }

    T* GetData() const{
        return Data;
    }
private:
    std::string DataKey;
    T* Data;
};

class FArchive {
public:

    FArchive() {
    };
    FArchive(const FArchive& Archive) {
        //TODO copy constructor
    };
    FArchive(FArchive&& Archive) noexcept {
        //TODO move constructor
    }
    virtual ~FArchive() {
        ArchiveDatas.Clear();
        SubArchives.Clear();
    };
    
    template<class T>
    void InsertDataInArchive(const std::string& Key, T& Data) {
        auto Field = TSerializableField<T>(Key, Data);
        *this << Field;
    }
    
    template<class T>
    void ReadDataInArchive(const std::string& Key, T& Data) {
        auto Field = TSerializableField<T>(Key, Data);
        *this >> Field;
    }

    template<class T>
    void InsertDataInArchive(const std::string& Key, T* Data) {
        if (Data != nullptr) {
            auto Field = TSerializableField<T>(Key, Data);
            *this << Field;
        }
    }
    
    template<class T>
    void ReadDataInArchive(const std::string& Key, T* Data) {
        if (Data != nullptr) {
            auto Field = TSerializableField<T>(Key, Data);
            *this >> Field;
        }
    }
private:
    template<SupportStringSerialization T>
    FArchive& operator<<(const TSerializableField<T>& Field) {
        FStream Stream = FStream();
        Stream.Stream() << Field.GetData();
        ArchiveDatas.Insert({Field.Key(), Stream.ToString()});
        return *this;
    }

    template<SupportStringSerialization T>
    FArchive& operator>>(TSerializableField<T>& Field) {
        FStream Stream = FStream(ArchiveDatas.Find(Field.Key()));
        Stream.Stream() >> *Field.GetData(); 
        return *this;
    }
public:
    FArchive& operator[](const std::string& Key) {
        if (!SubArchives.Contains(Key)) {
            SubArchives.Insert({Key, FArchive()});
        }
        return SubArchives.Find(Key);

    }
private:
    TMap<std::string, std::string> ArchiveDatas;
    TMap<std::string, FArchive> SubArchives;
    
};