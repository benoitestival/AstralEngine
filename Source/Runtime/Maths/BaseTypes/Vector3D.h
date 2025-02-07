#pragma once
#include "../Utils/BaseTypesForward.h"

template<typename T>
struct TVector3D {
    TVector3D();
    TVector3D(T XYZ);
    TVector3D(T X_, T Y_, T Z_);
public:
    T X;
    T Y;
    T Z;
};




#include "Vector3D.inl"
