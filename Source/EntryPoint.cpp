#include <iostream>

#include "Application.h"
#include "Runtime/Engine/CoreObjects/Objects/BaseObject.h"
#include "Runtime/RTTI/Field.h"

struct toto {
    
};

int main(int argc, char* argv[]){

    TArray<int> TestAAA = {};

    
    FArchive Ar;
    int test;
    FClass Class;
    ABaseObject* Test = new ABaseObject();
    Test->Serialize(Ar);
    // std::stringstream Stream;
    // Stream << "test";

    // toto tsttot;
    // Ar << tsttot;
    std::cout << "test";
    delete Test;
    Test = nullptr;

    
    Application* App = new Application();
    
    App->Start();
    
    delete App;
    App = nullptr;
    
    return 0;
 }
