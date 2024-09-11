#include "TestEngine.h"
#include <iostream>

#include "../../Runtime/Engine/CoreObjects/Entities/Entity.h"

void ATestEngine::Start() {
    AEngine::Start();

    AEntity Entity;
    FArchive Ar;
    int test = 1;

    //std::vector<std::pair<std::string, std::string>> TestArray;
    TArray<std::pair<std::string, std::string>> TestArray;
    std::pair<std::string, std::string> testPair = std::make_pair("", "");
    //TestArray.insert(testPair, 0);
    TestArray.Insert(testPair, 0);

    //std::vector<>
    //Ar << TSerializableField<int>("", test, 0);
    //Ar << TSerializableField<AEntity>("", Entity, 0);
    // FArchive Ar = FArchive(EArchiveType::ART_STRING);
    // int test;
    // FClass Class;
    // ABaseObject* Test = new ABaseObject();
    // Test->Serialize(Ar);
    //
    //
    //
    // delete Test;
    // Test = nullptr;

    std::cout << "test";
    
    End();
}
