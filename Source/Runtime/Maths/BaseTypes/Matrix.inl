#pragma once
#include "Matrix.h"

#include "Vector2D.h"
#include "Vector3D.h"

#define LENGHT2D 3
#define LENGHT3D 4

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(){
    InitMatrixArray();
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const TVector2D<T> Vector) : TMatrix<T, R, C>() {
    *this[0][0] = Vector.X;
    *this[0][1] = Vector.Y;
    *this[0][2] = 1;
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const TVector3D<T> Vector) : TMatrix<T, R, C>() {
    *this[0][0] = Vector.X;
    *this[0][1] = Vector.Y;
    *this[0][2] = Vector.Z;
    *this[0][3] = 1;
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
        for (int ROW_INDEX = 0; ROW_INDEX < R; ROW_INDEX++) {
            for (int COLUMN_INDEX = 0; COLUMN_INDEX < OtherC; COLUMN_INDEX++) {
                ResultMatrix[ROW_INDEX][COLUMN_INDEX] = MultiplyRowByColumn(*this[ROW_INDEX], OtherMatrix[COLUMN_INDEX]);
            }
        }
    }
    return ResultMatrix;
}

template <typename T, int R, int C>
T TMatrix<T, R, C>::MultiplyRowByColumn(const TArray<T> Row, const TArray<T> Column) {
    T Result = T();
    if (Row.Lenght() == Column.Lenght()) {
        for (int INDEX = 0; INDEX < Row.Lenght(); INDEX++) {
            Result = Result + Row[INDEX] * Column[INDEX];
        }
    }
    return Result;
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
TVector3D<T> TMatrix<T, R, C>::operator*(const TVector3D<T>& Vector) {
    TVector3D<T> ResultVector = Vector;
    if (R == C == LENGHT3D) {
        ResultVector = (*this * Vector.ToMatrix()).ToVector3D();
    }
    return ResultVector;
}

template <typename T, int R, int C>
TVector2D<T> TMatrix<T, R, C>::ToVector2D() const {
    return TVector2D<T>(*this[0][0], *this[0][1]);
}

template <typename T, int R, int C>
TVector3D<T> TMatrix<T, R, C>::ToVector3D() const {
    return TVector3D<T>(*this[0][0], *this[0][1], *this[0][2]);
}

template <typename T, int R, int C>
void TMatrix<T, R, C>::InitMatrixArray() {
    Matrix.assign(R, TArray<T>().assign(C));
}

