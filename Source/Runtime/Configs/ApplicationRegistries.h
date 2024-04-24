#pragma once
#include <string>
#include <unordered_map>
#include "../Utils/Factory.h"


#define REGISTER_ASTRAL_CLASS(Class)\
    ApplicationRegistries::RegisterClass(Class::StaticClass());\
    ApplicationRegistries::RegisterCreator(Class::StaticClass(), new DerivedCreator<ABaseObject, Class>());

#define REGISTER_ASTRAL_NO_FACTORY_CLASS(Class)\
    ApplicationRegistries::RegisterClass(Class::StaticClass());


struct FClass;

class ApplicationRegistries {
public:
    static void FillRegistries(); 
    static void ClearRegistries();

    static bool IsClassRegister(const std::string& ClassName);
    static bool IsCreatorRegister(const FClass* Class);
    
    static void RegisterClass(FClass* Class);
    static void RegisterCreator(FClass* Class, Creator<ABaseObject>* Creator);

    static FClass* GetClass(const std::string& ClassName);
    static Factory<ABaseObject>* GetCreatorFactory();
private:
    static std::unordered_map<std::string, FClass*> ClassRegistry; 
    static Factory<ABaseObject>* CreatorRegistry;
};
