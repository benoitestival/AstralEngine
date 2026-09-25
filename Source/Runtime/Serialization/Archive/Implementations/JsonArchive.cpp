#include "JsonArchive.h"

JsonArchive::JsonArchive(bool IsLoadingArchive) : FArchive(), IsLoadingArchiveType(IsLoadingArchive){
    ArchiveNodes.Add(&RootNode);
}


bool JsonArchive::LoadFromFile(const std::string& Path) {
    std::ifstream File(Path);
    if (!File.is_open()) return false;
    File >> RootNode;
    ArchiveNodes.Clear();
    ArchiveNodes.Add(&RootNode);
    return true;
}

void JsonArchive::SaveToFile(const std::string& Path) {
    std::ofstream File(Path);
    File << RootNode.dump(4);
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
