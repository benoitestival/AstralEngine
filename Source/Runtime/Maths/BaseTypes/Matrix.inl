#pragma once
#include "../Utils/CoreIncludes.h"

#define MAX_ROW_FROM_VECTOR 1

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(){
    InitMatrixArray(T());
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const T& Val) {
    InitMatrixArray(Val);
}

template <typename T, int R, int C>
TMatrix<T, R, C>::TMatrix(const TVector<T, C> Vector) {
    if (R == MAX_ROW_FROM_VECTOR) {
        for (int ROW_INDEX = 0; ROW_INDEX < R; ROW_INDEX++) {
            for (int COLUMN_INDEX = 0; COLUMN_INDEX < C; COLUMN_INDEX++) {
                if (COLUMN_INDEX < Vector.Num()) {
                    Matrix[ROW_INDEX][COLUMN_INDEX] = Vector[COLUMN_INDEX];
                }
                else {
                    Matrix[ROW_INDEX][COLUMN_INDEX] = 1.0f;
                }
            }
        }
    }
}


template <typename T, int R, int C>
TVector<T, C>* TMatrix<T, R, C>::operator[](int Index) {
    return &Matrix[Index];
}

template <typename T, int R, int C>
const TVector<T, C>* TMatrix<T, R, C>::operator[](int Index) const {
    return &Matrix[Index];
}

template <typename T, int R, int C>
template <int OtherR, int OtherC>
TMatrix<T, R, OtherC> TMatrix<T, R, C>::operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix) {
    TMatrix<T, R, OtherC> ResultMatrix = TMatrix<T, R, OtherC>();
    if (C == OtherR) {
        for (int ROW_INDEX = 0; ROW_INDEX < R; ROW_INDEX++) {
            for (int COLUMN_INDEX = 0; COLUMN_INDEX < OtherC; COLUMN_INDEX++) {

                for (int INDEX = 0; INDEX < C; INDEX++) {
                    ResultMatrix[ROW_INDEX][COLUMN_INDEX] += Matrix[ROW_INDEX][INDEX] * OtherMatrix[INDEX][COLUMN_INDEX];
                }
                
            }
        }
    }
    return ResultMatrix;
}

//TODO add concept for detecting square matrix
template <typename T, int R, int C>
TMatrix<T, R, C> TMatrix<T, R, C>::Identity() {
    TMatrix<T, R, C> IdentityMatrix = TMatrix<T, R, C>(T(0.0f));
    
    return IdentityMatrix;
}

template <typename T, int R, int C>
TVector<T, C> TMatrix<T, R, C>::ToVector() const {
    TVector<T, C> Vector = TVector<T, C>();
    for (int INDEX = 0; INDEX < 0; INDEX++) {
        
    }
    return Vector;
}

template <typename T, int R, int C>
void TMatrix<T, R, C>::InitMatrixArray(const T& Val) {
    for (int I = 0; I < R ; I++) {
        for (int J = 0; J < C ; J++) {
            Matrix[I][J] = Val;
        }
    }
}

