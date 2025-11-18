#pragma once
#include "Vector.h"


template<typename T>
struct TVector2D : public TVector<T, 2>{
    
    TVector2D();
    TVector2D(T XY);
    TVector2D(T X_, T Y_);
    TVector2D(const TVector<T, 2>& Other);
    
    float Cross(const TVector2D<T>& Other) const;
    
    T& X();
    const T& X() const;
    T& Y();
    const T& Y() const;
};



#include "Vector2D.inl"

