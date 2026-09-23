#pragma once
#include "../../Utils/Array.h"
#include "../../Utils/Map.h"
#include "../Utils/SerializationUtils.h"

class FArchive {
public:

    FArchive() = default;
    virtual ~FArchive() = default;

    virtual bool IsReading() = 0;
    
    //Basic type function
    virtual void Serialize(const std::string& Key, bool& Data) = 0;
    virtual void Serialize(const std::string& Key, int& Data) = 0;
    virtual void Serialize(const std::string& Key, float& Data) = 0;
    virtual void Serialize(const std::string& Key, std::string& Data) = 0;

    virtual void DeSerialize(const std::string& Key, bool& Data) = 0;
    virtual void DeSerialize(const std::string& Key, int& Data) = 0;
    virtual void DeSerialize(const std::string& Key, float& Data) = 0;
    virtual void DeSerialize(const std::string& Key, std::string& Data) = 0;

    //Nodes Function
    virtual void BeginSubNode(const std::string& NodeName){};
    virtual void EndSubNode(const std::string& NodeName){};

    //Containers Functions
    virtual void BeginContainer(const std::string& NodeName, int& Size){};
    virtual void EndContainer(){};
    
    virtual void BeginAnonymousElement() {};
    virtual void EndAnonymousElement() {};
    
    template<class DataType>
    void Serialize(const std::string& Key, DataType& Data) {
        if constexpr (ImplementSpecificSerialization<DataType>) {
            BeginSubNode(Key);
            Data.Serialize(*this);
            EndSubNode(Key);
        }
        else if constexpr (IsBasicType<DataType>){
            FArchive::Serialize(Key, Data);
        }
        else {
            //Add log not supported
        }
    }
    template<class DataType>
    void DeSerialize(const std::string& Key, DataType& Data) {
        if constexpr (ImplementSpecificSerialization<DataType>) {
            BeginSubNode(Key);
            Data.DeSerialize(*this);
            EndSubNode(Key);
        }
        else if constexpr (IsBasicType<DataType>){
            FArchive::DeSerialize(Key, Data);
        }
        else {
            //Add log not supported
        }
    }

    
    template<class DataType>
    void Serialize(const std::string& Key, DataType* Data) {
         Serialize(Key, *Data);
    }
    template<class DataType>
    void DeSerialize(const std::string& Key, DataType* Data) {
        //TODO make recreation of astral object here
        DeSerialize(Key, *Data);
    }
    
    template<class DataType>
    void Serialize(const std::string& Key, TArray<DataType>& Datas) {
        int Size = Datas.Lenght();
        BeginContainer(Key, Size);
        for (int INDEX = 0; INDEX < Datas.Lenght() ;INDEX++) {
            BeginAnonymousElement();
            Serialize<DataType>("", Datas[INDEX]);
            EndAnonymousElement();
        }
        EndContainer();
    }
    template<class DataType>
    void DeSerialize(const std::string& Key, TArray<DataType>& Datas) {

        int Size = 0;
        BeginContainer(Key, Size);
        Datas.Resize(Size);
        
        for (int INDEX = 0; INDEX < Datas.Lenght() ;INDEX++) {
            BeginAnonymousElement();
            DeSerialize<DataType>("", Datas[INDEX]);
            EndAnonymousElement();
        }
        EndContainer();
    }

    template<class DataKey, class DataType>
    void Serialize(const std::string& Key, TMap<DataKey, DataType>& Datas) {
        int Size = Datas.Lenght();
        BeginContainer(Key, Size);

        for (auto& Pair : Datas) {
            BeginAnonymousElement();

            DataKey KeyVal = Pair.first;//No ref to remove const and force copy
            Serialize<DataKey>("Key", KeyVal);

            DataType& DataVal = Pair.second;
            Serialize<DataType>("Value", DataVal);
            
            EndAnonymousElement();
        }
        EndContainer();
    }

    template<class DataKey, class DataType>
    void DeSerialize(const std::string& Key, TMap<DataKey, DataType>& Datas) {
        int Size = 0;
        BeginContainer(Key, Size);

        for (int INDEX = 0; INDEX < Size ;INDEX++) {
            BeginAnonymousElement();

            DataKey KeyVal = DataKey();
            DeSerialize<DataKey>("Key", KeyVal);

            DataType DataVal = DataType();
            DeSerialize<DataType>("Value", DataVal);

            Datas.Insert(KeyVal, DataVal);
            
            EndAnonymousElement();
        }
        EndContainer();
    }
};


