// ReSharper disable All
#include "DebugMain.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <glm/gtx/transform.hpp>

#include "../../Runtime/Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "../../Runtime/Engine/Engine/Engine.h"
#include "../../Runtime/Engine/Inputs/Components/InputComponent.h"
#include "../../Runtime/Engine/Inputs/Objects/InputAction.h"
#include "../../Runtime/Engine/Inputs/Systems/InpuManager.h"
#include "../../Runtime/Engine/Statics/GameplayStatics.h"
#include "../../Runtime/Serialization/Archive/Implementations/JsonArchive.h"

int ADebugMain::DebugMain() {

    // {
    //     JsonArchive WriteAr(false);
    //     int I = 42;
    //     float F = 3.14f;
    //     std::string S = "hello";
    //     bool B = true;
    //     WriteAr.Serialize("I", I);
    //     WriteAr.Serialize("F", F);
    //     WriteAr.Serialize("S", S);
    //     WriteAr.Serialize("B", B);
    //     WriteAr.SaveToFile("test_basic.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_basic.json");
    //     int I2 = 0; float F2 = 0; std::string S2; bool B2 = false;
    //     ReadAr.DeSerialize("I", I2);
    //     ReadAr.DeSerialize("F", F2);
    //     ReadAr.DeSerialize("S", S2);
    //     ReadAr.DeSerialize("B", B2);
    //
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  2. Type composé non-RTTI (FVector)
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     FTestVector Vec{1.0f, 2.0f, 3.0f};
    //     WriteAr.Serialize<FTestVector>("Vec", Vec);
    //     WriteAr.SaveToFile("test_vector.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_vector.json");
    //     FTestVector Vec2;
    //     ReadAr.DeSerialize<FTestVector>("Vec", Vec2);
    //
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  3. TArray de types basiques
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     TArray<int> Values = {1, 2, 3, 4, 5};
    //     WriteAr.Serialize("Values", Values);
    //     WriteAr.SaveToFile("test_array_basic.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_array_basic.json");
    //     TArray<int> Values2;
    //     ReadAr.DeSerialize("Values", Values2);
    //
    //     bool Match = Values2.Lenght() == 5;
    //     for (int I = 0; Match && I < Values.Lenght(); I++)
    //         Match = Values[I] == Values2[I];
    //
    //     CHECK(Match, "TArray<int> round-trip");
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  4. TArray de types composés non-RTTI
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     TArray<FTestVector> Vectors = { {1,2,3}, {4,5,6}, {7,8,9} };
    //     WriteAr.Serialize("Vectors", Vectors);
    //     WriteAr.SaveToFile("test_array_composite.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_array_composite.json");
    //     TArray<FTestVector> Vectors2;
    //     ReadAr.DeSerialize("Vectors", Vectors2);
    //
    //     bool Match = Vectors2.Lenght() == 3;
    //     for (int I = 0; Match && I < Vectors.Lenght(); I++)
    //         Match = Vectors[I] == Vectors2[I];
    //
    //     CHECK(Match, "TArray<FTestVector> (composite) round-trip");
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  5. TArray<TArray<int>> — imbrication de containers
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     TArray<TArray<int>> Matrix;
    //     Matrix.Add({1, 2});
    //     Matrix.Add({3, 4, 5});
    //     WriteAr.Serialize("Matrix", Matrix);
    //     WriteAr.SaveToFile("test_array_nested.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_array_nested.json");
    //     TArray<TArray<int>> Matrix2;
    //     ReadAr.DeSerialize("Matrix", Matrix2);
    //
    //     bool Match = Matrix2.Lenght() == 2
    //               && Matrix2[0].Lenght() == 2 && Matrix2[1].Lenght() == 3
    //               && Matrix2[0][0] == 1 && Matrix2[0][1] == 2
    //               && Matrix2[1][0] == 3 && Matrix2[1][1] == 4 && Matrix2[1][2] == 5;
    //
    //     CHECK(Match, "TArray<TArray<int>> (nested containers) round-trip");
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  6. TMap<std::string, int>
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     TMap<std::string, int> Scores;
    //     Scores.Insert("Alice", 10);
    //     Scores.Insert("Bob", 20);
    //     WriteAr.Serialize("Scores", Scores);
    //     WriteAr.SaveToFile("test_map.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_map.json");
    //     TMap<std::string, int> Scores2;
    //     ReadAr.DeSerialize("Scores", Scores2);
    //
    //     CHECK(Scores2.Lenght() == 2, "TMap<string,int> round-trip");
    //     // Ajuste selon l'API réelle de TMap pour vérifier les
    //     // valeurs elles-mêmes (Contains/Find/operator[])
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  7. Pointeur vers objet RTTI simple (polymorphisme + factory)
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     AWeapon* Sword = new AWeapon();
    //     Sword->Damage = 50;
    //     WriteAr.Serialize("Sword", Sword);
    //     WriteAr.SaveToFile("test_rtti_pointer.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_rtti_pointer.json");
    //     AWeapon* Sword2 = nullptr;
    //     ReadAr.DeSerialize("Sword", Sword2);
    //     
    //     delete Sword;
    //     delete Sword2;
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  8. Pointeur RTTI nul — vérifie le cas nullptr
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //     AWeapon* NoWeapon = nullptr;
    //     WriteAr.Serialize("NoWeapon", NoWeapon);
    //     WriteAr.SaveToFile("test_rtti_null.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_rtti_null.json");
    //     AWeapon* NoWeapon2 = nullptr;
    //     ReadAr.DeSerialize("NoWeapon", NoWeapon2);
    //
    // }
    //
    // // ═══════════════════════════════════════════════
    // //  9. Objet RTTI complet, imbriqué : pointeur RTTI dans un
    // //     objet RTTI, TArray de basiques, TArray de pointeurs RTTI
    // //     -- le test le plus complet, combine tout à la fois
    // // ═══════════════════════════════════════════════
    // {
    //     JsonArchive WriteAr(false);
    //
    //     AInventory* Inv = new AInventory();
    //     Inv->EquippedWeapon = new AWeapon();
    //     Inv->EquippedWeapon->Damage = 99;
    //     Inv->Slots = {1, 2, 3};
    //     Inv->Backpack.Add(new AWeapon());
    //     Inv->Backpack[0]->Damage = 10;
    //     Inv->Backpack.Add(new AWeapon());
    //     Inv->Backpack[1]->Damage = 20;
    //
    //     WriteAr.Serialize("Inventory", Inv);
    //     WriteAr.SaveToFile("test_full_nested.json");
    //
    //     JsonArchive ReadAr(true);
    //     ReadAr.LoadFromFile("test_full_nested.json");
    //     AInventory* Inv2 = nullptr;
    //     ReadAr.DeSerialize("Inventory", Inv2);
    //
    //     bool Match = Inv2 != nullptr
    //         && Inv2->EquippedWeapon != nullptr
    //         && Inv2->EquippedWeapon->Damage == 99
    //         && Inv2->Slots.Lenght() == 3
    //         && Inv2->Slots[0] == 1 && Inv2->Slots[1] == 2 && Inv2->Slots[2] == 3
    //         && Inv2->Backpack.Lenght() == 2
    //         && Inv2->Backpack[0]->Damage == 10
    //         && Inv2->Backpack[1]->Damage == 20;
    //
    //
    //     delete Inv->EquippedWeapon;
    //     delete Inv->Backpack[0];
    //     delete Inv->Backpack[1];
    //     delete Inv;
    //     delete Inv2->EquippedWeapon;
    //     delete Inv2->Backpack[0];
    //     delete Inv2->Backpack[1];
    //     delete Inv2;
    // }
    
    return CONTINUE_CODE;
    //return EXIT_CODE;
}
