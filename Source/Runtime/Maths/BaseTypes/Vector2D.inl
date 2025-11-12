#pragma once
#include <iostream>
#include "Matrix.h"

#define LENGHT2D 2

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

template<typename T, IsNumber N>
TVector2D<T> operator*(N Number, const TVector2D<T>& V){
    return V * Number;
}


template <typename T>
TMatrix<T, 1, 2> TVector2D<T>::ToMatrix() const {
    return TMatrix<T, 1, 2>(*this);
}

template <typename T>
TMatrix<T, 1, 3> TVector2D<T>::ToTransformMatrix() const {
    return TMatrix<T, 1, 3>(*this);
}

template <typename T>
TVector2D<T> TVector2D<T>::operator*(const TMatrix<T, 2, 2>& Other) const{
    return (ToMatrix() * Other).ToVector2D();
}

template <typename T>
TVector2D<T> TVector2D<T>::operator*(const TMatrix<T, 3, 3>& Other) const{
    return (ToTransformMatrix() * Other).ToVector2D();
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
float TVector2D<T>::Lenght() const {
    return FMath::Sqrt(FMath::Square(X) + FMath::Square(Y));
}

template <typename T>
float TVector2D<T>::Dot(const TVector2D& Other) const {
    return X * Other.X + Y * Other.Y;  

}

template <typename T>
float TVector2D<T>::Cross(const TVector2D<T>& Other) const {
    return X * Other.Y - Y * Other.X;
}

template <typename T>
void TVector2D<T>::Log() const {
    std::cout << "X: " << X << "; Y: " << Y << std::endl;
}

template <typename T>
int TVector2D<T>::Num() const{
    return LENGHT2D;
}

