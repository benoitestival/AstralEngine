#pragma once
#include "../Objects/BaseObject.h"

class AManager : public ABaseObject {
public:
    AManager() = default;
    DECLARE_ASTRAL_ENGINE_CLASS(AManager, ABaseObject)
    // [[nodiscard]] virtual FClass* GetClass() override { return AManager::StaticClass(); };
    // [[nodiscard]] static FClass* StaticClass() {
    //     static FClass* Class = []() {
    //         TArray<FClass*> Parents = {ABaseObject::StaticClass(),};
    //         return AstralEngineStatics::IsClassRegister("AManager") ? AstralEngineStatics::GetClass("AManager") : AstralEngineStatics::RegisterClassInternal<AManager>(TClassConstructor<AManager>::ConstructClass("AManager"), Parents);
    //     }();
    //     return Class;
    // }; inline static const FClassAutoRegister AutoReg_AManager{ &AManager::StaticClass }; using Super = ABaseObject;

    virtual void Init();
    virtual void DeInit();
};
