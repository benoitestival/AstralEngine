#pragma once
#include "../Utils/MathUtility.h"

#define LENGHT3D 3


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
TMatrix<T, 1, 3> TVector3D<T>::ToMatrix() const {
    return TMatrix<T, 1, 3>(*this);
}

template <typename T>
TMatrix<T, 1, 4> TVector3D<T>::ToTransformMatrix() const {
    return TMatrix<T, 1, 4>(*this);
}

template <typename T>
TVector3D<T> TVector3D<T>::operator*(const TMatrix<T, 3, 3>& Other) const{
    return (ToMatrix() * Other).ToVector3D();
}

template <typename T>
TVector3D<T> TVector3D<T>::operator*(const TMatrix<T, 4, 4>& Other) const{
    return (ToTransformMatrix() * Other).ToVector3D();
}


template <typename T>
float TVector3D<T>::Lenght() const {
    return FMath::Sqrt(FMath::Square(X) + FMath::Square(Y) + FMath::Square(Z));
}

template <typename T>
int TVector3D<T>::Num() const {
    return LENGHT3D;
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

