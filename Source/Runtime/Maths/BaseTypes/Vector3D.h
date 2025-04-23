#pragma once
#include "../Utils/BaseTypesForward.h"

template<typename T>
struct TVector3D {
    TVector3D();
    TVector3D(T XYZ);
    TVector3D(T X_, T Y_, T Z_);

    bool operator==(const TVector3D& Other) const;
    bool operator!=(const TVector3D& Other) const;
    
    TVector3D operator+(const TVector3D& Other) const;
    TVector3D operator-(const TVector3D& Other) const;
    TVector3D operator*(const TVector3D& Other) const;
    TVector3D operator/(const TVector3D& Other) const;

    TVector3D operator+(const T& Other) const;
    TVector3D operator-(const T& Other) const;
    TVector3D operator*(const T& Other) const;
    TVector3D operator/(const T& Other) const;

    TMatrix<T, 1, 3> ToMatrix() const;
    TMatrix<T, 1, 4> ToTransformMatrix() const;
    TVector3D operator*(const TMatrix<T, 3, 3>& Other) const;
    TVector3D operator*(const TMatrix<T, 4, 4>& Other) const;
    
    float Lenght() const;
    int Num() const;
    
    void Normalize();
    void SafeNormalize();

    float Dot(const TVector3D<T>& Other) const;
    TVector3D<T> Cross(const TVector3D<T>& Other) const;
    
    
public:
    T X;
    T Y;
    T Z;
};




#include "Vector3D.inl"
