#include "Application.h"
#include "Runtime/RTTI/Field.h"
#include "Runtime/Serialization/Archive.h"

int main(int argc, char* argv[]){

    FArchive Ar;
    int test;
    FClass Class;
    Ar.AddField("test", test);
    Ar.AddField("test2", Class);
    
    Application* App = new Application();
    
    App->Start();
    
    delete App;
    App = nullptr;
    
    return 0;
 }
