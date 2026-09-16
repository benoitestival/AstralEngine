#pragma once
#include <string>
#include <unordered_map>

#include "../RTTI/RTTI.h"
#include "../Utils/Array.h"
#include "../Utils/Factory.h"
#include "../Utils/Map.h"
#include "../Utils/TemplateUtils.h"


// #define REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, ...)\
//     if(!AstralEngineStatics::IsClassRegister(#Class)){\
//         FClass* Instance##Class = CREATE_RTTI_BASE_CLASS_INSTANCE(Class);\
//         AstralEngineStatics::RegisterClass(Instance##Class);\
//     }\
//
// #define REGISTER_ASTRAL_SINGLETON_CLASS(Class, ...)\
//     REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, __VA_ARGS__)

// #define REGISTER_ASTRAL_PURE_CLASS(Class, ...)\
//     REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, __VA_ARGS__)


class Application;
struct FClass;

class AstralEngineStatics {
public:
    static void InitAstralEngineStatics(Application* App); 
    static void ClearAstralEngineStatics();

    static bool IsClassRegister(const std::string& ClassName);

    template<class T>
    static FClass* RegisterClassInternal(FClass* Class, const TArray<FClass*>& Parents) {
        Class->AddParents(Parents);
        GetClassRegistry().Insert(std::make_pair(Class->GetClassName(), Class));

        if (Class->IsFactoryEligible()) {
            if constexpr (IsClassConstructible<T>()){//Safety compilation check in case the class is abstract but we forgot to marked it
                AstralEngineStatics::RegisterCreatorInternal(Class, new DerivedCreator<ABaseObject, T>());
            }
        }
        GetClassRegistry().Insert(std::make_pair(Class->GetClassName(), Class));
        
        return Class;
    }
    
    static void RegisterCreatorInternal(FClass* Class, Creator<ABaseObject>* Creator);

    static Application* GetApp();

    static FClass* GetClass(const std::string& ClassName);
    static Creator<ABaseObject>* GetCreator(const FClass* Class);

    static TArray<FClass*> GetAllRegistredClasses();
    static TArray<FClass*> GetAllFactoryClasses();
private:
    static Application* AstralEngineApp ;

    static TMap<std::string, FClass*>& GetClassRegistry(){
        static TMap<std::string, FClass*> Instance;
        return Instance;
    }

    static TMap<std::string, Creator<ABaseObject>*>& GetCreatorRegistry(){
        static TMap<std::string, Creator<ABaseObject>*> Instance;
        return Instance;
    }
    
    // static TMap<std::string, FClass*> ClassRegistry; 
    // static TMap<std::string, Creator<ABaseObject>*> CreatorRegistry;
};
    
