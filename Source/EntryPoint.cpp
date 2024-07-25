#include <iostream>

#include "Application.h"
#include "Runtime/Engine/CoreObjects/Objects/BaseObject.h"
#include "Runtime/RTTI/Field.h"

struct toto {
    
};

int main(int argc, char* argv[]){
    Application* App = new Application();
    
    App->Start();
    
    delete App;
    App = nullptr;
    
    return 0;
 }
