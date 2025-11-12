#pragma once

template <typename T>
TRotator<T>::TRotator() {
}

template <typename T>
TRotator<T>::TRotator(T InValue) : Roll(InValue), Picth(InValue), Yaw(InValue){
}

template <typename T>
TRotator<T>::TRotator(T InRoll, T InPitch, T InYaw) : Roll(InRoll), Picth(InPitch), Yaw(InYaw){
}

template <typename T>
TVector3D<T> TRotator<T>::ToVector() const {
    return {};//TODO
}
