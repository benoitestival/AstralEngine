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
    
    TMatrix<T, 1, 4> ToMatrix() const;
public:
    T X;
    T Y;
    T Z;
};




#include "Vector3D.inl"
