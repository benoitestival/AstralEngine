#include "JsonArchive.h"

JsonArchive::JsonArchive(bool IsLoadingArchive, EChecksumType ArChecksumType) : FArchive(ArChecksumType), IsLoadingArchiveType(IsLoadingArchive){
    ArchiveNodes.Add(&RootNode);
}

void JsonArchive::SerializeChecksum(TArray<char>& Checksum) {
    
    std::string CheckSumString = std::string();
    CheckSumString.resize(Checksum.Lenght() * 2);

    for (int INDEX = 0; INDEX < CheckSumString.length(); INDEX+=2) {
        uint8_t Byte = static_cast<uint8_t>(Checksum[INDEX]);
        CheckSumString[INDEX] = ConvertDecimalToHex(Byte >> 4);
        CheckSumString[INDEX + 1] = ConvertDecimalToHex(Byte & 0xF);
    }
    
    Serialize("Checksum", CheckSumString);
}

TArray<char> JsonArchive::DeserializeChecksum() {
    std::string CheckSumString = std::string();
    DeSerialize("Checksum", CheckSumString);
    RootNode.erase("Checksum");

    TArray<char> Checksum = TArray<char>();
    for (int INDEX = 0; INDEX < CheckSumString.length(); INDEX+=2) {
        char FirstHalf = ConvertHexToDecimal(CheckSumString[INDEX]);
        char SecondHalf = ConvertHexToDecimal(CheckSumString[INDEX + 1]);
        
        char CompleteChar = 0;
        CompleteChar += FirstHalf << 4;
        CompleteChar |= SecondHalf;
        
        Checksum.Add(CompleteChar);
    }
    
    return Checksum;
}

char JsonArchive::ConvertDecimalToHex(char Num) {
    static char HexDigits[17] = "0123456789ABCDEF";
    return HexDigits[Num];
}

char JsonArchive::ConvertHexToDecimal(char Num) {
    return Num <= '9' ? Num - '0' : Num - 'A' + 10;
}

TArray<char> JsonArchive::GetArchiveRawDatas() {
    std::string ArchiveString = RootNode.dump();
    return {std::vector<char>(ArchiveString.begin(), ArchiveString.end())};
}

void JsonArchive::SetArchiveRawDatas(TArray<char>& RawDatas) {
    std::string Text(RawDatas.Data(), RawDatas.Lenght());
    RootNode = JsonObject::parse(Text);
    ArchiveNodes.Clear();
    AnonymousReadIteratorStack.Clear();
    ArchiveNodes.Add(&RootNode);
}


void JsonArchive::Serialize(const std::string& Key, bool& Data) {
    WriteData(Key, Data);
}

void JsonArchive::Serialize(const std::string& Key, int& Data) {
    WriteData(Key, Data);
}

void JsonArchive::Serialize(const std::string& Key, float& Data) {
    WriteData(Key, Data);
}

void JsonArchive::Serialize(const std::string& Key, std::string& Data) {
    WriteData(Key, Data);
}

void JsonArchive::DeSerialize(const std::string& Key, bool& Data) {
    ReadData(Key, Data);
}

void JsonArchive::DeSerialize(const std::string& Key, int& Data) {
    ReadData(Key, Data);
}

void JsonArchive::DeSerialize(const std::string& Key, float& Data) {
    ReadData(Key, Data);
}

void JsonArchive::DeSerialize(const std::string& Key, std::string& Data) {
    ReadData(Key, Data);
}

void JsonArchive::BeginSubNode(const std::string& NodeName) {
    if (!NodeName.empty()) {
        if (IsReading()) {
            JsonObject& SubNode = GetCurrentNode()[NodeName];
            ArchiveNodes.Add(&SubNode);
        }
        else {
            GetCurrentNode()[NodeName] = JsonObject::object();
            ArchiveNodes.Add(&GetCurrentNode()[NodeName]);
        }
    }
}

void JsonArchive::EndSubNode(const std::string& NodeName) {
    if (!NodeName.empty()) {
        ArchiveNodes.RemoveAt(ArchiveNodes.LastIndex());
    }
}

void JsonArchive::BeginContainer(const std::string& NodeName, int& Size) {
    if (!NodeName.empty()) {
        if (IsReading()) {
            JsonObject& SubNode = GetCurrentNode()[NodeName];
            ArchiveNodes.Add(&SubNode);//Push subnode so its the new current node

            Size = SubNode.size();
        
            AnonymousReadIteratorStack.Add(SubNode.begin());//Register actual node as a container
        }
        else {
            GetCurrentNode()[NodeName] = JsonObject::array();
            ArchiveNodes.Add(&GetCurrentNode()[NodeName]);
        }
    }
    else {
        //Test if name is empty then its an array in an array so we still need the size
        if (IsReading()) {
            Size = GetCurrentNode().size();
            AnonymousReadIteratorStack.Add(GetCurrentNode().begin());
            //On bouge juste le curseur le reste est gérer par anonymous event
        }
    }
}

void JsonArchive::EndContainer(const std::string& NodeName) {
    if (IsReading()) {
        AnonymousReadIteratorStack.RemoveAt(AnonymousReadIteratorStack.LastIndex());
    }
    if (!NodeName.empty()) {
        ArchiveNodes.RemoveAt(ArchiveNodes.LastIndex());
    }
}

void JsonArchive::BeginAnonymousElement() {
    if (IsReading()) {
        JsonObject& SubNode = *AnonymousReadIteratorStack.Last();//Get the next one in the current array node register
        ++AnonymousReadIteratorStack.Last();//Move forward in the array node 
        ArchiveNodes.Add(&SubNode);
    }
    else {
        GetCurrentNode().push_back(JsonObject(nullptr));
        ArchiveNodes.Add(&GetCurrentNode().back());
    }
}

void JsonArchive::EndAnonymousElement() {
    ArchiveNodes.RemoveAt(ArchiveNodes.LastIndex());
}

bool JsonArchive::IsReading() {
    return IsLoadingArchiveType;
}

JsonObject& JsonArchive::GetCurrentNode() {
    return *ArchiveNodes.Last();
}
