#pragma once
#include "../Utils/MathUtility.h"
#include "Matrix.h"

template <typename T, int Size>
TMatrix<T, 1, Size> TVector<T, Size>::ToMatrix() const {
    return TMatrix<T, 1, Size>(*this);
}

template <typename T, int Size>
TMatrix<T, 1, Size + 1> TVector<T, Size>::ToHomogeneousMatrix() const {
    return TMatrix<T, 1, Size + 1>(*this);
}

template <typename T, int Size>
bool TVector<T, Size>::operator==(const TVector<T, Size>& Other) const {
    bool Result = true;
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        if (Datas[CoordIndex] != Other[CoordIndex]) {
            Result = false;
        }
    }
    return Result;
}

template <typename T, int Size>
bool TVector<T, Size>::operator!=(const TVector<T, Size>& Other) const {
    return !(*this) == Other;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator+(const TVector<T, Size>& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] + Other[CoordIndex];
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator-(const TVector<T, Size>& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] - Other[CoordIndex];
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator*(const TVector<T, Size>& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] * Other[CoordIndex];
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator/(const TVector<T, Size>& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] / Other[CoordIndex];
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator+(const T& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] + Other;
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator-(const T& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] - Other;
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator*(const T& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] * Other;
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator/(const T& Other) const {
    TVector<T, Size> Result = TVector();
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        Result[CoordIndex] = Datas[CoordIndex] / Other;
    }
    return Result;
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator*(const TMatrix<T, Size, Size>& Other) const {
    return (ToMatrix() * Other).ToVector();
}

template <typename T, int Size>
TVector<T, Size> TVector<T, Size>::operator*(const TMatrix<T, Size + 1, Size + 1>& Other) const {
    return (ToHomogeneousMatrix() * Other).ToVector2D();
}

template <typename T, int Size>
T& TVector<T, Size>::operator[](int Index) {
    return Datas[Index];
}

template <typename T, int Size>
const T& TVector<T, Size>::operator[](int Index) const{
    return Datas[Index];
}

template <typename T, int Size>
int TVector<T, Size>::Num() const {
    return Size;
}

template <typename T, int Size>
float TVector<T, Size>::Dot(const TVector<T, Size>& Other) const {
    float DotResult = 0.0f;
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        DotResult += static_cast<float>(Datas[CoordIndex]) * static_cast<float>(Other[CoordIndex]);
    }
    return DotResult;
}

template <typename T, int Size>
void TVector<T, Size>::Normalize() {
    *this = *this/Lenght();
}

template <typename T, int Size>
void TVector<T, Size>::SafeNormalize() {
    if (Lenght() > 0) {
        Normalize();
    }
}

template <typename T, int Size>
TVector<T, Size> operator+(const T& OtherN, const TVector<T, Size>& OtherV) {
    return OtherV + OtherN;
}

template <typename T, int Size>
TVector<T, Size> operator-(const T& OtherN, const TVector<T, Size>& OtherV) {
    return OtherV - OtherN;
}

template <typename T, int Size>
TVector<T, Size> operator*(const T& OtherN, const TVector<T, Size>& OtherV) {
    return OtherV * OtherN;
}

template <typename T, int Size>
TVector<T, Size> operator/(const T& OtherN, const TVector<T, Size>& OtherV) {
    return OtherV / OtherN;
}

template <typename T, int Size>
float TVector<T, Size>::Lenght() const {
    float SquareSum = 0;
    for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
        SquareSum += FMath::Pow(static_cast<float>(Datas[CoordIndex]), 2);
    }
    return FMath::Sqrt(SquareSum);
}
