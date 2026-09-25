#include "BinaryArchive.h"

#include <fstream>

BinaryArchive::BinaryArchive(bool IsLoadingArchive) : IsReadingArchive(IsLoadingArchive), ReadOffset(0){
}

bool BinaryArchive::LoadFromFile(const std::string& Path) {
    bool Success = false;
    
    std::ifstream Stream = std::ifstream(Path, std::ifstream::binary);
    if (Stream.is_open()) {
        int Size = std::filesystem::file_size(Path);
        Buffer.Resize(Size);
        Stream.read(Buffer.Data(), Size);

        if (!Stream.fail()) {            
            ReadOffset = 0;                
            Success = true;             
        }
    }
    return Success;
}

void BinaryArchive::SaveToFile(const std::string& Path) {
    std::ofstream Stream = std::ofstream(Path, std::ofstream::binary);
    if (Stream.is_open()) {
        Stream.write(Buffer.Data(), Buffer.Lenght());
    }
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

