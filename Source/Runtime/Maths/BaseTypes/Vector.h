#pragma once
#include "Utils/BaseTypesForward.h"

template<typename T, int Size>
struct TVector {
    TVector() = default;

    //Matrix Conversion
    TMatrix<T, 1, Size> ToMatrix() const;
    TMatrix<T, 1, Size + 1> ToHomogeneousMatrix() const;
    
    //Boolean Operators
    bool operator==(const TVector<T, Size>& Other) const;
    bool operator!=(const TVector<T, Size>& Other) const;
    
    //Maths operators
    TVector<T, Size> operator+(const TVector<T, Size>& Other) const;
    TVector<T, Size> operator-(const TVector<T, Size>& Other) const;
    TVector<T, Size> operator*(const TVector<T, Size>& Other) const;
    TVector<T, Size> operator/(const TVector<T, Size>& Other) const;
    
    TVector<T, Size> operator+(const T& Other) const;
    TVector<T, Size> operator-(const T& Other) const;
    TVector<T, Size> operator*(const T& Other) const;
    TVector<T, Size> operator/(const T& Other) const;

    TVector<T, Size> operator*(const TMatrix<T, Size, Size>& Other) const;
    TVector<T, Size> operator*(const TMatrix<T, Size + 1, Size + 1>& Other) const;

    //Access operators
    T& operator[](int Index);
    const T& operator[](int Index) const;
    
    //Common Vector methods in any dimension
    int Num() const;
    float Lenght() const;
    
    float Dot(const TVector<T, Size>& Other) const;

    void Normalize();
    void SafeNormalize();

protected:
    T Datas[Size];
};

template<typename T, int Size>
TVector<T, Size> operator+(const T& OtherN, const TVector<T, Size>& OtherV);
template<typename T, int Size>
TVector<T, Size> operator-(const T& OtherN, const TVector<T, Size>& OtherV);
template<typename T, int Size>
TVector<T, Size> operator*(const T& OtherN, const TVector<T, Size>& OtherV);
template<typename T, int Size>
TVector<T, Size> operator/(const T& OtherN, const TVector<T, Size>& OtherV);

#include "Vector.inl"