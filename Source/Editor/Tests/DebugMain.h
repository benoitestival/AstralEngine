#pragma once
#include "../../Runtime/Engine/CoreObjects/Objects/BaseObject.h"

#include <cstddef>
#include <stdexcept>


// template<typename T>
// class Vector {
//
//
// public:
//     Vector() : Data(nullptr), Capacity(0), Size(0) {}
//
//     ~Vector() {
//         delete[] Data;
//     }
//     
//     void push_back(const T& value) {
//         if (Size >= Capacity) {
//             resize(Capacity == 0 ? 1 : Capacity * 2);
//         }
//         Data[Size++] = value;
//     }
//
//     void insert(size_t index, const T& value) {
//         if (index > Size) return; // ⚠️ ERREUR SUBTILE : insert silencieusement ignoré si index trop grand
//         if (Size >= Capacity) {
//             resize(Capacity * 2); // ⚠️ ERREUR GRAVE : si capacity == 0, mul 0 → pas de place
//         }
//         for (size_t i = Size; i > index; --i) {
//             Data[i] = Data[i - 1]; // ⚠️ Peut écrire hors limite si pas de redimensionnement correct
//         }
//         Data[index] = value;
//         ++Size;
//     }
//
//     void remove(size_t index) {
//         if (index >= Size) return; // ⚠️ Pas d’exception, comportement silencieux et potentiellement dangereux
//         for (size_t i = index; i < Size - 1; ++i) {
//             Data[i] = Data[i + 1];
//         }
//         --Size;
//         // ⚠️ ERREUR SUBTILE : pas de destruction de l’élément supprimé (si T a un destructeur)
//     }
//
//     size_t getSize() const { return Size; }
//
//    
//
// private:
//     void resize(size_t newCapacity) {
//         T* newData = new T[newCapacity];
//         for (size_t i = 0; i <= Size; ++i) { // ⚠️ ERREUR GRAVE : boucle va jusqu’à size INCLUS
//             newData[i] = Data[i];
//         }
//         delete[] Data;
//         Data = newData;
//         Capacity = newCapacity;
//     }
//     
// private:
//     T* Data;
//     size_t Capacity;
//     size_t Size;
//
//    
// };

//
// template<typename T>
// class Vector {
//
// public:
//     Vector() : Data(nullptr), Capacity(0), Size(0) {}
//     ~Vector() = default;
//     
//     void Add(const T Value) {
//         Size = Size + 1;
//         Data[Size] = Value;
//     }
//
//     void Insert(int Index, const T Value) {
//         if (Index < Size) {
//             if (Size >= Capacity) {
//                 Resize(Capacity * 2);
//             }
//             for (int i = Size; i > Index; i--) {
//                 Data[i] = Data[i - 1];
//             }
//         }
//         Data[Index] = Value;
//         Size = Size + 1;
//     }
//
//     void Remove(int Index) {
//         for (int i = Index; i <= Size - 1; i++) {
//             Data[i] = Data[i + 1];
//         }
//         Size = Size - 1;
//     }
//     
// private:
//     void Resize(int NewCapacity) {
//         T* newData = new T[NewCapacity];
//         for (int i = 0; i < Size; i++) {
//             newData[i] = Data[i];
//         }
//         delete[] Data;
//         Data = newData;
//     }
//     
// private:
//     T* Data;
//     int Capacity;
//     int Size;
// };

class ADebugMain : public  ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ADebugMain, ABaseObject)


    
    
    int DebugMain();
};
