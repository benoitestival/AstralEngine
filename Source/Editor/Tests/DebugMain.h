#pragma once
#include "../../Runtime/Engine/CoreObjects/Objects/BaseObject.h"

#include <cstddef>
#include <stdexcept>


struct FTestVector {
    float X = 0, Y = 0, Z = 0;

    void Serialize(FArchive& Ar) {
        Ar.Serialize("X", X);
        Ar.Serialize("Y", Y);
        Ar.Serialize("Z", Z);
    }
    void DeSerialize(FArchive& Ar) {
        Ar.DeSerialize("X", X);
        Ar.DeSerialize("Y", Y);
        Ar.DeSerialize("Z", Z);
    }

    bool operator==(const FTestVector& Other) const {
        return X == Other.X && Y == Other.Y && Z == Other.Z;
    }
};

// ─────────────────────────────────────────────────────────────────
//  Types RTTI — testent la factory (nom de classe, IsAstralObject,
//  reconstruction polymorphique). AInventory contient un AWeapon*
//  imbriqué, pour vérifier le cas "objet RTTI dans un objet RTTI".
// ─────────────────────────────────────────────────────────────────
class AWeapon : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AWeapon, ABaseObject)

    int Damage = 0;

    void Serialize(FArchive& Ar) override {
        Super::Serialize(Ar);
        Ar.Serialize("Damage", Damage);
    }
    void DeSerialize(FArchive& Ar) override {
        Super::DeSerialize(Ar);
        Ar.DeSerialize("Damage", Damage);
    }
};

class AInventory : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInventory, ABaseObject)

    AWeapon* EquippedWeapon = nullptr;   // pointeur RTTI imbriqué
    TArray<int> Slots;                    // TArray de type basique
    TArray<AWeapon*> Backpack;            // TArray de pointeurs RTTI

    void Serialize(FArchive& Ar) override {
        Super::Serialize(Ar);
        Ar.Serialize("EquippedWeapon", EquippedWeapon);
        Ar.Serialize("Slots", Slots);
        Ar.Serialize("Backpack", Backpack);
    }
    void DeSerialize(FArchive& Ar) override {
        Super::DeSerialize(Ar);
        Ar.DeSerialize("EquippedWeapon", EquippedWeapon);
        Ar.DeSerialize("Slots", Slots);
        Ar.DeSerialize("Backpack", Backpack);
    }
};

class ADebugMain : public  ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ADebugMain, ABaseObject)

    
    
    
    int DebugMain();
};
