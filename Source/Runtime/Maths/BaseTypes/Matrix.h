#pragma once
#include "Vector.h"
#include "../Utils/BaseTypesForward.h"

template<typename T, int R, int C>
struct TMatrix {
public:
    TMatrix();
    TMatrix(const T& Val);
    TMatrix(const TVector<T, C> Vector);

    TVector<T, C>* operator[](int Index);
    const TVector<T, C>* operator[](int Index) const;

    template<int OtherR, int OtherC>
    TMatrix<T, R, OtherC> operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix);
    static TMatrix<T, R, C> Identity();
public:
    TVector<T, C> ToVector() const;
private:
    void InitMatrixArray(const T& Val);
private:
    TVector<T, C> Matrix[R]; //N dimension matrix represented by an array of vector of N size (currently only supported is 2D and 3D)
};

#include "Matrix.inl"
