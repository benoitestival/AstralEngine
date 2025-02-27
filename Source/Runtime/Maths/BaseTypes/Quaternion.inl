#pragma once
#include "Quaternion.h"


template <typename T>
TQuat<T>::TQuat() {
}

template <typename T>
TQuat<T>::TQuat(T InValue) : W(InValue), X(InValue), Y(InValue), Z(InValue){
}

template <typename T>
TQuat<T>::TQuat(T InW, T InX, T InY, T InZ) : W(InW), X(InX), Y(InY), Z(InZ){
}

template <typename T>
TQuat<T>::TQuat(TVector3D<T>& InVec, T InAngle) {
}

template <typename T>
TQuat<T>::TQuat(TRotator<T>& InRot) {
}

template <typename T>
TQuat<T>::TQuat(TMatrix<T, 4, 4>& InMatrix) {
}
