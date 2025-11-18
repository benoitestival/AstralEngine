#pragma once



template <typename T>
TVector3D<T>::TVector3D() : TVector3D(T()){
}

template <typename T>
TVector3D<T>::TVector3D(T XYZ) {
    this->Datas[0] = XYZ;
    this->Datas[1] = XYZ;
    this->Datas[1] = XYZ;
}

template <typename T>
TVector3D<T>::TVector3D(T X_, T Y_, T Z_) {
    this->Datas[0] = X_;
    this->Datas[1] = Y_;
    this->Datas[2] = Z_;
}

template <typename T>
TVector3D<T>::TVector3D(const TVector<T, 3>& Other) {
    this->Datas[0] = Other[0];
    this->Datas[1] = Other[1];
    this->Datas[2] = Other[2];
}

template <typename T>
TVector3D<T> TVector3D<T>::Cross(const TVector3D<T>& Other) const {
    TVector3D<T> Result = TVector3D<T>();
    Result.X() = Y() * Other.Z() - Z() * Other.Y();
    Result.Y() = Z() * Other.X() - X() * Other.Z();
    Result.Z() = X() * Other.Y() - Y() * Other.X();
    return Result;
}

template <typename T>
T& TVector3D<T>::X() {
    return this->Datas[0];
}

template <typename T>
const T& TVector3D<T>::X() const {
    return this->Datas[0];
}

template <typename T>
T& TVector3D<T>::Y() {
    return this->Datas[1];
}

template <typename T>
const T& TVector3D<T>::Y() const {
    return this->Datas[1];
}

template <typename T>
T& TVector3D<T>::Z() {
    return this->Datas[2];
}

template <typename T>
const T& TVector3D<T>::Z() const {
    return this->Datas[2];
}

