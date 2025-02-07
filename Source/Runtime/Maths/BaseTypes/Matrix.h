#pragma once
#include "../Utils/CoreIncludes.h"
#include "../Utils/BaseTypesForward.h"

#define LENGHT2D 3

template<typename T, int R, int C>
struct TMatrix {
public:
    TMatrix();
    TMatrix(const TVector2D<T> Vector);
    TMatrix(const TVector3D<T> Vector);

    TArray<T>& operator[](int Index);

    template<int OtherR, int OtherC>
    TMatrix<T, R, OtherC> operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix);
    TVector2D<T> operator*(const TVector2D<T>& Vector);


    TVector2D<T> ToVector2D() const;
private:
    void InitMatrixArray();
    
public:
    // int RowNumbers = 0;
    // int ColumnNumbers = 0;

private:
    TArray<TArray<T>> Matrix;
};



#include "Matrix.inl"
