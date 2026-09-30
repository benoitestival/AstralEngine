#include "BinaryArchive.h"

BinaryArchive::BinaryArchive(bool IsLoadingArchive, EChecksumType ArChecksumType) : FArchive(ArChecksumType), IsReadingArchive(IsLoadingArchive), ReadOffset(0){
}

void BinaryArchive::SerializeChecksum(TArray<char>& Checksum) {
    Buffer.Append(Checksum);
}

TArray<char> BinaryArchive::DeserializeChecksum() {
    TArray<char> Checksum= TArray<char>();

    for (int INDEX = Buffer.Lenght() - GetCheckSumSize(); INDEX < Buffer.Lenght(); INDEX++) {
        Checksum.Add(Buffer[INDEX]);
    }
    
    for (int INDEX = Buffer.Lenght() - 1; INDEX >= Buffer.Lenght() - GetCheckSumSize(); INDEX--) {
        Buffer.RemoveAt(INDEX);
    }
    return Checksum;
}

TArray<char> BinaryArchive::GetArchiveRawDatas() {
    return Buffer;
}

void BinaryArchive::SetArchiveRawDatas(TArray<char>& RawDatas) {
    Buffer = RawDatas;
    ReadOffset = 0;
}

void BinaryArchive::Serialize(const std::string& Key, bool& Data) {
    SerializeRaw(reinterpret_cast<char*>(&Data), sizeof(bool));
}

void BinaryArchive::Serialize(const std::string& Key, int& Data) {
    SerializeRaw(reinterpret_cast<char*>(&Data), sizeof(int));
}

void BinaryArchive::Serialize(const std::string& Key, float& Data) {
    SerializeRaw(reinterpret_cast<char*>(&Data), sizeof(float));
}

void BinaryArchive::Serialize(const std::string& Key, std::string& Data) {
    int Size = Data.size();
    SerializeRaw(reinterpret_cast<char*>(&Size), sizeof(int));
    SerializeRaw(Data.data(), Size);  }

void BinaryArchive::DeSerialize(const std::string& Key, bool& Data) {
    DeSerializeRaw(reinterpret_cast<char*>(&Data), sizeof(bool));
}

void BinaryArchive::DeSerialize(const std::string& Key, int& Data) {
    DeSerializeRaw(reinterpret_cast<char*>(&Data), sizeof(int));
}

void BinaryArchive::DeSerialize(const std::string& Key, float& Data) {
    DeSerializeRaw(reinterpret_cast<char*>(&Data), sizeof(float));
}

void BinaryArchive::DeSerialize(const std::string& Key, std::string& Data) {
    int Size = 0;
    DeSerializeRaw(reinterpret_cast<char*>(&Size), sizeof(int));
    Data.resize(Size);
    
    DeSerializeRaw(Data.data(), Size);   
}

void BinaryArchive::SerializeRaw(char* Data, int Size) {
    int BufferLenght = Buffer.Lenght();
    Buffer.Resize(BufferLenght + Size);

    std::memcpy(Buffer.Data() + BufferLenght, Data, Size);
}

void BinaryArchive::DeSerializeRaw(char* Data, int Size) {
    std::memcpy(Data, Buffer.Data() + ReadOffset, Size);
    ReadOffset = ReadOffset + Size;
}


void BinaryArchive::BeginContainer(const std::string& NodeName, int& Size) {
    if (IsReading()) {
        DeSerializeRaw(reinterpret_cast<char*>(&Size), sizeof(int));
    }
    else {
        SerializeRaw(reinterpret_cast<char*>(&Size), sizeof(int));
    }
}

bool BinaryArchive::IsReading() {
    return IsReadingArchive;
}

