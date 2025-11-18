#pragma once
#include "Vector.h"

template<typename T>
struct TVector3D : public TVector<T, 3>{
    TVector3D();
    TVector3D(T XYZ);
    TVector3D(T X_, T Y_, T Z_);
    TVector3D(const TVector<T, 3>& Other);

    TVector3D<T> Cross(const TVector3D<T>& Other) const;
    
    T& X();
    const T& X() const;
    T& Y();
    const T& Y() const;
    T& Z();
    const T& Z() const;
};




#include "Vector3D.inl"
