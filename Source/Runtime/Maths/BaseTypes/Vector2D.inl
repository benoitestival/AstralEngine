#pragma once
#include <iostream>
#include "Vector2D.h"
#include "Matrix.h"

template <typename T>
TVector2D<T>::TVector2D() {
}

template <typename T>
TVector2D<T>::TVector2D(T XY)  : X(XY), Y(XY){
}

template <typename T>
TVector2D<T>::TVector2D(T X_, T Y_) : X(X_), Y(Y_){
}

template <typename T>
bool TVector2D<T>::operator==(const TVector2D& Other) const {
    return X == Other.X && Y == Other.Y;
}

template <typename T>
bool TVector2D<T>::operator!=(const TVector2D& Other) const {
    return !(*this == Other);
}

template <typename T>
TVector2D<T> TVector2D<T>::operator+(const TVector2D& Other) const {
    TVector2D Result = TVector2D();
    Result.X = X + Other.X;
    Result.Y = Y + Other.Y;
    return Result;
}

template <typename T>
TVector2D<T> TVector2D<T>::operator-(const TVector2D& Other) const {
    TVector2D Result = TVector2D();
    Result.X = X - Other.X;
    Result.Y = Y - Other.Y;
    return Result;
}


template <typename T>
TVector2D<T> TVector2D<T>::operator*(const TVector2D& Other) const {
    TVector2D Result = TVector2D();
    Result.X = X * Other.X;
    Result.Y = Y * Other.Y;
    return Result;
}

template <typename T>
TVector2D<T> TVector2D<T>::operator/(const TVector2D& Other) const {
    TVector2D Result = TVector2D();
    Result.X = X / Other.X;
    Result.Y = Y / Other.Y;
    return Result;
}

template <typename T>
TVector2D<T> TVector2D<T>::operator+(const T& Other) const {
    return *this + TVector2D(Other);
}

template <typename T>
TVector2D<T> TVector2D<T>::operator-(const T& Other) const {
    return *this - TVector2D(Other);
}

template <typename T>
TVector2D<T> TVector2D<T>::operator*(const T& Other) const {
    return *this * TVector2D(Other);
}

template <typename T>
TVector2D<T> TVector2D<T>::operator/(const T& Other) const {
    return *this / TVector2D(Other);
}

template <typename T>
void TVector2D<T>::SafeNormalize() {
    if (Lenght() > 0) {
        Normalize();
    }
}

template <typename T>
void TVector2D<T>::Normalize() {
    *this = *this/Lenght();
}

template <typename T>
float TVector2D<T>::Lenght() {
    return std::sqrt(std::pow(X, 2) + std::pow(Y, 2));
}

template <typename T>
float TVector2D<T>::Dot(const TVector2D& Other) const {
    return X * Other.X + Y * Other.Y;  

}

template <typename T>
float TVector2D<T>::Dot(const TVector2D& A, const TVector2D& B) {
    return A.Dot(B);
}

template <typename T>
void TVector2D<T>::Log() const {
    std::cout << "X: " << X << "; Y: " << Y << std::endl;
}

template <typename T>
TMatrix<T, 1, 3> TVector2D<T>::ToMatrix() const {
    return TMatrix<T, 1, 3>(*this);
}
