#pragma once

template<typename T>
struct TVector3D {
    TVector3D(){};
    TVector3D(T XYZ) : X(XYZ), Y(XYZ), Z(XYZ){};
    TVector3D(T X_, T Y_, T Z_) : X(X_), Y(Y_), Z(Z_){};
public:
    T X;
    T Y;
    T Z;
};