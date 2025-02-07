#pragma once
#include "Matrix.h"

#include "Vector2D.h"
#include "Vector3D.h"

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(){
    InitMatrixArray();
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const TVector2D<T> Vector) : TMatrix<T, R, C>() {
    *this[0][0] = Vector.X;
    *this[1][0] = Vector.Y;
    *this[2][0] = 1;
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const TVector3D<T> Vector) : TMatrix<T, R, C>() {
    *this[0][0] = Vector.X;
    *this[1][0] = Vector.Y;
    *this[2][0] = Vector.Z;
    *this[3][0] = 1;
}

template <typename T, int R, int C>
TArray<T>& TMatrix<T, R, C>::operator[](int Index) {
    return Matrix[Index];
}

template <typename T, int R, int C>
template <int OtherR, int OtherC>
TMatrix<T, R, OtherC> TMatrix<T, R, C>::operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix) {
    TMatrix<T, R, OtherC> ResultMatrix = TMatrix<T, R, OtherC>();
    if (C == OtherR) {
        //TODO the multiplication
    }
    return ResultMatrix;
}

template <typename T, int R, int C>
TVector2D<T> TMatrix<T, R, C>::operator*(const TVector2D<T>& Vector) {
    TVector2D<T> ResultVector = Vector;
    if (R == C == LENGHT2D) {
        ResultVector = (*this * Vector.ToMatrix()).ToVector2D();
    }
    return ResultVector;
}

template <typename T, int R, int C>
TVector2D<T> TMatrix<T, R, C>::ToVector2D() const {
    return TVector2D<T>(*this[0][1], *this[1][0]);
}

template <typename T, int R, int C>
void TMatrix<T, R, C>::InitMatrixArray() {
    Matrix.assign(R, TArray<T>().assign(C));
}
