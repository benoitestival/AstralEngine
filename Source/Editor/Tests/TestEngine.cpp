#include "TestEngine.h"

#include <iostream>

void ATestEngine::Start() {
    AEngine::Start();

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
