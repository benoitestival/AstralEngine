#pragma once
#include "../../Utils/Array.h"
#include "../../Utils/Map.h"
#include "../Utils/SerializationUtils.h"
#include "SerializableField.h"

#define MAP_KEY "MAP_KEY_ELEMENT"
#define MAP_VALUE "MAP_KEY_VALUE"

#define ARRAY_KEY "ARRAY_KEY"
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
        SubArchives.Clear();
    };
    
    template<class T>
    void InsertDataInArchive(const std::string& Key, T& Data, int DataIndex = 0) {
        InsertDataInArchive(TSerializableField<T>(Key, Data, DataIndex));
    }
    template<class T>
    void InsertDataInArchive(const std::string& Key, T* Data, int DataIndex = 0) {
        if (Data != nullptr) {
            InsertDataInArchive(TSerializableField<T>(Key, Data, DataIndex));
        }
    }

    template<class T>
    void InsertDataInArchive(const TSerializableField<T>& Field){
        *this << Field;
    }

    
    template<class T>
    void ReadDataInArchive(const std::string& Key, T& Data, int DataIndex = 0) {
        ReadDataInArchive(TSerializableField<T>(Key, Data, DataIndex));
    }
    
    template<class T>
    void ReadDataInArchive(const std::string& Key, T* Data, int DataIndex = 0) {
        if (Data != nullptr) {
             ReadDataInArchive(TSerializableField<T>(Key, Data, DataIndex));
        }
    }

    template<class T>
    void ReadDataInArchive(const TSerializableField<T>& Field) {
        *this >> Field;
    }
    
private:
    ///////////////////BASIC STRING SERIALIZABLE/////////////////////
    template<SupportStringSerialization T>
    FArchive& operator<<(const TSerializableField<T>& Field) {
        FStream Stream = FStream();
        Stream.Stream() << Field.GetData();
        ArchiveData = {Field.Key(), Stream.ToString()};
        return *this;
    }

    template<SupportStringSerialization T>
    FArchive& operator>>(const TSerializableField<T>& Field) {
        FStream Stream = FStream(ArchiveData.second);
        Stream.Stream() >> *Field.GetData(); 
        return *this;
    }

    /////////////////ASTRA OBJECT SERIALIZABLE////////////////////

    template<SupportAstralObjectSerialization T>
    FArchive& operator<<(const TSerializableField<T>& AstralObjectField) {
        if (AstralObjectField.GetData() != nullptr) {
            AstralObjectField.GetData()->Serialize(this);
        }
       return *this;
    }

    template<SupportAstralObjectSerialization T>
    FArchive& operator>>(TSerializableField<T>& AstralObjectField) {
        if (AstralObjectField.GetData() != nullptr) {
            AstralObjectField.GetData()->Deserialize(this);
        }
        return *this;
    }

    /////////////////CONTAINER SERIALIZABLE//////////////////////
    template<class K, class T>
    FArchive& operator<<(const TSerializableField<TMap<K,T>>& MapField) {
        FArchive MapArchive = SubArchive(MapField.Key());

        MapArchive << TSerializableField<int>("MapSize", MapField.GetData()->Lenght());
        for (auto& MapElement : *MapField.GetData()) {
            MapArchive.SubArchive(MapField.Key(), SubArchives.Lenght()).InsertDataInArchive(TSerializableField<K>(MAP_KEY, MapElement.first));
            MapArchive.SubArchive(MapField.Key(), SubArchives.Lenght()).InsertDataInArchive(TSerializableField<K>(MAP_VALUE, MapElement.second));
        }
        return *this;
    }

    template<class K, class T>
    FArchive& operator>>(const TSerializableField<TMap<K,T>>& MapField) {
        FArchive MapArchive = SubArchive(MapField.Key());
        
        int MapSize = 0;
        MapArchive >> TSerializableField<int>("MapsSize", MapSize);
        for (int Index = 0; Index < MapSize * 2; Index+= 2) {
            K KeyElement;
            T ValueElement;
        
            MapArchive.SubArchive(MapField.Key(), Index).ReadDataInArchive(TSerializableField<K>(MAP_KEY, KeyElement));
            MapArchive.SubArchive(MapField.Key(), Index + 1).ReadDataInArchive(TSerializableField<K>(MAP_VALUE, ValueElement));
        
            MapField.GetData()->Insert({KeyElement, ValueElement});
        }
        return *this;
    }

    template<class T>
    FArchive& operator<<(const TSerializableField<TArray<T>>& ArrayField) {
        FArchive ArrayArchive = SubArchive(ArrayField.Key());

        ArrayArchive << TSerializableField<int>("ArraySize", ArrayField.GetData()->Lenght());
        for (auto& ArrayElem : *ArrayField.GetData()) {
            ArrayArchive.SubArchive(ArrayField.Key(), SubArchives.Lenght()).InsertDataInArchive(TSerializableField<T>(ARRAY_KEY, ArrayElem));
        }
        return *this;
    }

    template<class K, class T>
    FArchive& operator>>(const TSerializableField<TArray<T>>& ArrayField) {
        FArchive ArrayArchive = SubArchive(ArrayField.Key());
        
        int ArraySize = 0;
        ArrayArchive >> TSerializableField<int>("ArraySize", ArraySize);
        for (int Index = 0; Index < ArraySize; Index++) {
            T ValueElement;
        
            ArrayArchive.SubArchive(ArrayField.Key(), Index).ReadDataInArchive(TSerializableField<K>(MAP_KEY, ValueElement));
        
            ArrayField.GetData()->Add(ValueElement);
        }
        return *this;
    }

    FArchive& SubArchive(const std::string& Key, int SuffixOffset = -1) {
        std::string FinalKey = Key;
        if (SuffixOffset >= 0) {
            FinalKey = FinalKey + std::to_string(SuffixOffset);
        }
        if (!SubArchives.Contains(Key)) {
            SubArchives.Insert({FinalKey, FArchive()});
        }
        return SubArchives.Find(Key);
    }
public:
    FArchive& operator[](const std::string& Key) {
        return SubArchive(Key);
    }
private:
    std::pair<std::string, std::string> ArchiveData;
    TMap<std::string, FArchive> SubArchives;
    
};