#pragma once
#include "Vector.h"
#include "../Utils/BaseTypesForward.h"

template<typename T, int R, int C>
struct TMatrix {
public:
    TMatrix();
    TMatrix(const T& Val);
    TMatrix(const TVector2D<T> Vector);
    TMatrix(const TVector3D<T> Vector);

    T* operator[](int Index);
    const T* operator[](int Index) const;

    template<int OtherR, int OtherC>
    TMatrix<T, R, OtherC> operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix);
    static TMatrix<T, R, C> Identity();
public:
    TVector2D<T> ToVector2D() const;
    TVector3D<T> ToVector3D() const;
private:
    void InitMatrixArray(const T& Val);
private:
    TVector<T, C> Matrix[R]; //N dimension matrix represented by an array of vector of N size (currently only supported is 2D and 3D)
};

#include "Matrix.inl"
