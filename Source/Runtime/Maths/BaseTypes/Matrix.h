#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "../Utils/Array.h"

template<typename T, int R, int C>
struct TMatrix {
public:
    TMatrix() : RowNumbers(R), ColumnNumbers(C) {
        Matrix.assign(RowNumbers, TArray<T>().assign(ColumnNumbers));
    };
    TMatrix(const TVector2D<T> Vector) {
        RowNumbers = 1;
        ColumnNumbers = 3;

        
    }
    TMatrix(const TVector3D<T> Vector) {
        
    }
    
    TMatrix<T,R,C> operator*(const TMatrix<T,R,C>& Other) {
        TMatrix<T, R, C> ReturnMatrix;
        //TODO
        return ReturnMatrix;
    }

    friend TVector2D<T> operator*(const TVector2D<T>& Vec, const TMatrix<T, 3, 3>& Matrix) {
        TVector2D<T> ReturnVector;
        //TODO
        return ReturnVector;
    }

    friend TVector3D<T> operator*(const TVector3D<T>& Vec, const TMatrix<T, 4, 4>& Matrix) {
        TVector3D<T> ReturnVector;
        //TODO
        return ReturnVector;
    }
public:
    int RowNumbers = 0;
    int ColumnNumbers = 0;

private:
    TArray<TArray<T>> Matrix;
};

