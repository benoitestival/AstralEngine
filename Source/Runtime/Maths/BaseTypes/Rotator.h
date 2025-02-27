#pragma once
#include "../Utils/BaseTypesForward.h"

template<typename T>
struct TRotator {
    TRotator();
    TRotator(T InValue);
    TRotator(T InRoll, T InPitch, T InYaw);

    TVector3D<T> ToVector() const;
public:
    T Roll;
    T Picth;
    T Yaw;
    
};


#include "Rotator.inl"
