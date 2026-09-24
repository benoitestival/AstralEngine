#pragma once
#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../../RTTI/Field.h"
#include "../../Utils/Array.h"
#include "../../Utils/Map.h"
#include "../../Utils/TemplateUtils.h"
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
    virtual void EndContainer(const std::string& NodeName){};
    
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
        if constexpr (IsAstralObject<DataType>()) {
            BeginSubNode(Key);//New node for an Astral object from pointer

            //we do this its polymorphic and need to save FClass
            std::string ClassName = Data->GetClass()->GetClassName();
            Serialize("ASTRAL_CLASS", ClassName);
            
            Data.Serialize(*this);
            EndSubNode(Key);
        }
        else {
            Serialize(Key, *Data);
        }
    }
    template<class DataType>
    void DeSerialize(const std::string& Key, DataType*& Data) {//Pass pointer by ref because we need to change the adress and the data its pointing to
        if constexpr (IsAstralObject<DataType>()) {
            BeginSubNode(Key);//New node for an Astral object from pointer

            //we do this its polymorphic and need to load FClass
            std::string ClassName;
            DeSerialize("ASTRAL_CLASS", ClassName);
            FClass* Class = AstralEngineStatics::GetClass(ClassName);
            
            if (Class != nullptr) {
                Data = NewObject<DataType>(Class);
                Data.DeSerialize(*this);
            }
            EndSubNode(Key);
        }
        else {
            DeSerialize(Key, *Data);    
        }
    }
    
    template<class DataType>
    void Serialize(const std::string& Key, TArray<DataType>& Datas) {
        int Size = Datas.Lenght();
        BeginContainer(Key, Size);
        for (int INDEX = 0; INDEX < Datas.Lenght() ;INDEX++) {
            BeginAnonymousElement();
            Serialize("", Datas[INDEX]);
            EndAnonymousElement();
        }
        EndContainer(Key);
    }
    template<class DataType>
    void DeSerialize(const std::string& Key, TArray<DataType>& Datas) {

        int Size = 0;
        BeginContainer(Key, Size);
        Datas.Resize(Size);
        
        for (int INDEX = 0; INDEX < Datas.Lenght() ;INDEX++) {
            BeginAnonymousElement();
            DeSerialize("", Datas[INDEX]);
            EndAnonymousElement();
        }
        EndContainer(Key);
    }

    template<class DataKey, class DataType>
    void Serialize(const std::string& Key, TMap<DataKey, DataType>& Datas) {
        int Size = Datas.Lenght();
        BeginContainer(Key, Size);

        for (auto& Pair : Datas) {
            BeginAnonymousElement();

            DataKey KeyVal = Pair.first;//No ref to remove const and force copy
            Serialize("Key", KeyVal);

            DataType& DataVal = Pair.second;
            Serialize("Value", DataVal);
            
            EndAnonymousElement();
        }
        EndContainer(Key);
    }

    template<class DataKey, class DataType>
    void DeSerialize(const std::string& Key, TMap<DataKey, DataType>& Datas) {
        int Size = 0;
        BeginContainer(Key, Size);

        for (int INDEX = 0; INDEX < Size ;INDEX++) {
            BeginAnonymousElement();

            DataKey KeyVal = DataKey();
            DeSerialize("Key", KeyVal);

            DataType DataVal = DataType();
            DeSerialize("Value", DataVal);

            Datas.Insert(KeyVal, DataVal);
            
            EndAnonymousElement();
        }
        EndContainer(Key);
    }
};