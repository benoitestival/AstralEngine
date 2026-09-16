#include "AstralEngineStatics.h"

Application* AstralEngineStatics::AstralEngineApp = nullptr;
//TMap<std::string, FClass*> AstralEngineStatics::ClassRegistry = {};
//TMap<std::string, Creator<ABaseObject>*> AstralEngineStatics::CreatorRegistry = {};

void AstralEngineStatics::InitAstralEngineStatics(Application* App) {
    AstralEngineApp = App;
    // RegisterAstralClasses();
    // LinkAstralClassesParents();
}

void AstralEngineStatics::ClearAstralEngineStatics() {
    GetClassRegistry().Clear();
    GetCreatorRegistry().Clear();
}

bool AstralEngineStatics::IsClassRegister(const std::string& ClassName) {
    return GetClassRegistry().Contains(ClassName);
}

// bool AstralEngineStatics::IsCreatorRegister(const FClass* Class) {
//     return CreatorRegistry.Contains(Class->GetClassName());
// }

void AstralEngineStatics::RegisterCreatorInternal(FClass* Class, Creator<ABaseObject>* Creator) {
    GetCreatorRegistry().Insert(std::make_pair(Class->GetClassName(), Creator));
}

Application* AstralEngineStatics::GetApp() {
    return AstralEngineApp;
}

FClass* AstralEngineStatics::GetClass(const std::string& ClassName) {
    return GetClassRegistry().Find(ClassName);
}

Creator<ABaseObject>* AstralEngineStatics::GetCreator(const FClass* Class) {
    return GetCreatorRegistry().Find(Class->GetClassName());
}

TArray<FClass*> AstralEngineStatics::GetAllRegistredClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : GetClassRegistry()) {
        Classes.Add(KeyVal.second);
    }
    return Classes;
}

TArray<FClass*> AstralEngineStatics::GetAllFactoryClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : GetClassRegistry()) {
        if (GetCreatorRegistry().Contains(KeyVal.second->GetClassName())) {
            Classes.Add(KeyVal.second);
        }
    }
    return Classes;
}

