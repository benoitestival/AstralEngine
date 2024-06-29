#include <iostream>

#include "Application.h"
#include "Runtime/Engine/CoreObjects/Objects/BaseObject.h"
#include "Runtime/RTTI/Field.h"

int main(int argc, char* argv[]){

    FArchive Ar;
    int test;
    FClass Class;
    ABaseObject* Test = new ABaseObject();
    Test->Serialize(Ar);
    // std::stringstream Stream;
    // Stream << "test";
    
    std::cout << "test";
    delete Test;
    Test = nullptr;

    
    Application* App = new Application();
    
    App->Start();
    
    delete App;
    App = nullptr;
    
    return 0;
 }
