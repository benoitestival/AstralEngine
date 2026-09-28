#pragma once

#include "../Utils/SerializationCoreIncludes.h"

#include "../Utils/SerializationUtils.h"
#include "../../Configs/AstralEngineStatics.h"
#include "../../Engine/CoreObjects/Utils/ObjectCoreUtility.h"

class FArchive {
public:

    FArchive(EChecksumType ArChecksumType) : ChecksumType(ArChecksumType) {
    };
    virtual ~FArchive() = default;

    virtual bool IsReading() = 0;

    //Security Functions
    TArray<char> ComputeChecksum(const TArray<char>& RawDatas) {
        TArray<char> Checksum = TArray<char>();
        if (ChecksumType == EChecksumType::ECT_CRC32) {
            uint32_t CRC32Checksum = SerializationUtils::BuildCRC32(RawDatas);
            
            Checksum.Resize(CRC32Checksum);
            std::memcpy(Checksum.Data(), reinterpret_cast<char*>(&CRC32Checksum), sizeof(CRC32Checksum));
        }
        else if (ChecksumType == EChecksumType::ECT_XXHASH32) {
            uint32_t xxHash32Checksum = SerializationUtils::BuildxxHash32(RawDatas);

            Checksum.Resize(xxHash32Checksum);
            std::memcpy(Checksum.Data(), reinterpret_cast<char*>(&xxHash32Checksum), sizeof(xxHash32Checksum));
        }
        return Checksum;
    }
    
    bool AreChecksumEqual(const TArray<char>& ChecksumOne, const TArray<char>& ChecksumTwo) {
        bool IsValid = false;
        if (ChecksumOne.Lenght() == ChecksumTwo.Lenght()) {
            int CorrectBytes = 0;
            for (int i = 0; i < ChecksumOne.Lenght(); ++i) {
                if (ChecksumOne[i] == ChecksumTwo[i]) {
                    CorrectBytes++;
                }
            }
            IsValid = CorrectBytes == ChecksumOne.Lenght();
        }
        return IsValid;
    };
    int GetCheckSumSize() {
        int Size = 0;
        if (ChecksumType == EChecksumType::ECT_CRC32) {
            Size = 4;
        }
        return Size;
    }
    
    //Files functions
    bool LoadFromFile(const std::string& Path) {
        bool SuccessfullySaved = false;

        std::ifstream Stream = std::ifstream(Path, std::ifstream::binary);
        if (Stream.is_open()) {
            
            TArray<char> Checksum = TArray<char>();
            Checksum.Resize(GetCheckSumSize());
            Stream.read(Checksum.Data(), GetCheckSumSize());
            
            int FileSize = std::filesystem::file_size(Path) - GetCheckSumSize();
            TArray<char> RawDatas = TArray<char>();
            RawDatas.Resize(FileSize);
            Stream.read(RawDatas.Data(), FileSize);

            if (AreChecksumEqual(Checksum, ComputeChecksum(RawDatas))) {
                SetArchiveRawDatas(RawDatas); 
                SuccessfullySaved = true;
            }
            
        }
        return SuccessfullySaved;

    };
    void SaveToFile(const std::string& Path) {
        std::ofstream Stream = std::ofstream(Path, std::ofstream::binary);
        if (Stream.is_open()) {
            TArray<char> RawDatas = GetArchiveRawDatas();
            TArray<char> Checksum = ComputeChecksum(RawDatas);
            
            Stream.write(Checksum.Data(), GetCheckSumSize());
            Stream.write(RawDatas.Data(), RawDatas.Lenght());
        }
    };
    
    virtual TArray<char> GetArchiveRawDatas() = 0;
    virtual void SetArchiveRawDatas(TArray<char>& RawDatas) = 0;
    
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
            
            Data->Serialize(*this);
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
                Data->DeSerialize(*this);
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
    
private:
    EChecksumType ChecksumType;
};