#pragma once
#include "Vector3D.h"

template <typename T>
TVector3D<T>::TVector3D() {
}

template <typename T>
TVector3D<T>::TVector3D(T XYZ)  : X(XYZ), Y(XYZ), Z(XYZ){
}

template <typename T>
TVector3D<T>::TVector3D(T X_, T Y_, T Z_) : X(X_), Y(Y_), Z(Z_) {
}
