#include "TestEngine.h"

void ATestEngine::Start() {
    AEngine::Start();

    FArchive Ar = FArchive(EArchiveType::ART_STRING);
    int test;
    FClass Class;
    ABaseObject* Test = new ABaseObject();
    Test->Serialize(Ar);

    
    
    delete Test;
    Test = nullptr;
    
    End();
}
