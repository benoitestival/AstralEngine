#include "Application.h"
#include "Runtime/RTTI/Field.h"
#include "Runtime/Serialization/Archive.h"

int main(int argc, char* argv[]){
    Application* App = new Application();
    
    App->Start();
    
    delete App;
    App = nullptr;
    
    return 0;
 }
