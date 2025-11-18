#pragma once

template <typename T>
TVector2D<T>::TVector2D() : TVector2D(T()){
}

template <typename T>
TVector2D<T>::TVector2D(T XY){
    this->Datas[0] = XY;
    this->Datas[1] = XY;
}

template <typename T>
TVector2D<T>::TVector2D(T X_, T Y_){
    this->Datas[0] = X_;
    this->Datas[1] = Y_;
}

template <typename T>
TVector2D<T>::TVector2D(const TVector<T, 2>& Other) {
    this->Datas[0] = Other[0];
    this->Datas[1] = Other[1];
}

template <typename T>
float TVector2D<T>::Cross(const TVector2D<T>& Other) const {
    return X() * Other.Y() - Y() * Other.X();
}

template <typename T>
T& TVector2D<T>::X() {
    return this->Datas[0];
    
}

template <typename T>
const T& TVector2D<T>::X() const{
    return this->Datas[0];
}

template <typename T>
T& TVector2D<T>::Y() {
    return this->Datas[1];
}

template <typename T>
const T& TVector2D<T>::Y() const {
    return this->Datas[1];
}

