#pragma once
#include "../Utils/BaseTypesForward.h"

template<typename T>
struct TVector2D {
    
    TVector2D();
    TVector2D(T XY);
    TVector2D(T X_, T Y_);

    bool operator==(const TVector2D& Other) const;
    bool operator!=(const TVector2D& Other) const;

    TVector2D operator+(const TVector2D& Other) const;
    TVector2D operator-(const TVector2D& Other) const;
    TVector2D operator*(const TVector2D& Other) const;
    TVector2D operator/(const TVector2D& Other) const;

    TVector2D operator+(const T& Other) const;
    TVector2D operator-(const T& Other) const;
    TVector2D operator*(const T& Other) const;
    TVector2D operator/(const T& Other) const;

    TMatrix<T, 1, 2> ToMatrix() const;
    TMatrix<T, 1, 3> ToTransformMatrix() const;
    TVector2D operator*(const TMatrix<T, 2, 2>& Other) const;
    TVector2D operator*(const TMatrix<T, 3, 3>& Other) const;
    
    void Normalize();
    void SafeNormalize();
    
    float Lenght() const;
    
    float Dot(const TVector2D& Other) const;
    float Cross(const TVector2D<T>& Other) const;
    
    void Log() const;
    int Num() const;
    
public:
    T X;
    T Y;
    
};



#include "Vector2D.inl"

