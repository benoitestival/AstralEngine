#pragma once

#include "../Utils/BaseTypesForward.h"

template<typename T>
struct TQuat {
public:
    TQuat();
    TQuat(T InValue);
    TQuat(T InW, T InX, T InY, T InZ);
    TQuat(TVector3D<T>& InVec, T InAngle);
    TQuat(TRotator<T>& InRot);
    TQuat(TMatrix<T, 4, 4>& InMatrix);

public:
    T W;
    T X;
    T Y;
    T Z;
};



#include "Quaternion.inl"
