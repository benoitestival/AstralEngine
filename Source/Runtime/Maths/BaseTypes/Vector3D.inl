#pragma once
#include "Vector3D.h"
#include "../Utils/MathUtility.h"


template <typename T>
TVector3D<T>::TVector3D() {
}

template <typename T>
TVector3D<T>::TVector3D(T XYZ)  : X(XYZ), Y(XYZ), Z(XYZ){
}

template <typename T>
TVector3D<T>::TVector3D(T X_, T Y_, T Z_) : X(X_), Y(Y_), Z(Z_) {
}

template <typename T>
bool TVector3D<T>::operator==(const TVector3D& Other) const {
    return X == Other.X && Y == Other.Y && Z == Other.Z;
}

template <typename T>
bool TVector3D<T>::operator!=(const TVector3D& Other) const {
    return !(*this == Other);
}

template <typename T>
TVector3D<T> TVector3D<T>::operator+(const TVector3D& Other) const {
    TVector3D Result = TVector3D();
    Result.X = X + Other.X;
    Result.Y = Y + Other.Y;
    Result.Z = Z + Other.Z;
    return Result;
}

template <typename T>
TVector3D<T> TVector3D<T>::operator-(const TVector3D& Other) const {
    TVector3D Result = TVector3D();
    Result.X = X - Other.X;
    Result.Y = Y - Other.Y;
    Result.Z = Z - Other.Z;
    return Result;
}

template <typename T>
TVector3D<T> TVector3D<T>::operator*(const TVector3D& Other) const {
    TVector3D Result = TVector3D();
    Result.X = X * Other.X;
    Result.Y = Y * Other.Y;
    Result.Z = Z * Other.Z;
    return Result;
}

template <typename T>
TVector3D<T> TVector3D<T>::operator/(const TVector3D& Other) const {
    TVector3D Result = TVector3D();
    Result.X = X / Other.X;
    Result.Y = Y / Other.Y;
    Result.Z = Z / Other.Z;
    return Result;
}

template <typename T>
TVector3D<T> TVector3D<T>::operator+(const T& Other) const {
    return *this + TVector3D(Other);
}

template <typename T>
TVector3D<T> TVector3D<T>::operator-(const T& Other) const {
    return *this - TVector3D(Other);
}

template <typename T>
TVector3D<T> TVector3D<T>::operator*(const T& Other) const {
    return *this * TVector3D(Other);
}

template <typename T>
TVector3D<T> TVector3D<T>::operator/(const T& Other) const {
    return *this / TVector3D(Other);
}

template <typename T>
float TVector3D<T>::Lenght() const {
    return FMath::Sqrt(FMath::Square(X) + FMath::Square(Y) + FMath::Square(Z));
}

template <typename T>
void TVector3D<T>::Normalize() {
    *this / Lenght();
}

template <typename T>
void TVector3D<T>::SafeNormalize() {
    if (Lenght() > 0) {
        Normalize();
    }
}

template <typename T>
float TVector3D<T>::Dot(const TVector3D<T>& Other) const {
    return X * Other.X + Y * Other.Y + Z * Other.Z;
}

template <typename T>
TVector3D<T> TVector3D<T>::Cross(const TVector3D<T>& Other) const {
    TVector3D<T> Result = TVector3D<T>();
    Result.X = Y * Other.Z - Z * Other.Y;
    Result.Y = Z * Other.X - X * Other.Z;
    Result.Z = X * Other.Y - Y * Other.X;
    return Result;
}

template <typename T>
TMatrix<T, 1, 4> TVector3D<T>::ToMatrix() const {
    return TMatrix<T, 1, 4>(*this);
}
