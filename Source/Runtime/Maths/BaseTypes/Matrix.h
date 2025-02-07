#pragma once
#include "../Utils/CoreIncludes.h"
#include "../Utils/BaseTypesForward.h"

template<typename T, int R, int C>
struct TMatrix {
public:
    TMatrix();
    TMatrix(const TVector2D<T> Vector);
    TMatrix(const TVector3D<T> Vector);

    TArray<T>& operator[](int Index);

    template<int OtherR, int OtherC>
    TMatrix<T, R, OtherC> operator*(const TMatrix<T, OtherR, OtherC>& OtherMatrix);
private:
    T MultiplyRowByColumn(const TArray<T> Row, const TArray<T> Column);
public:
    TVector2D<T> operator*(const TVector2D<T>& Vector);
    TVector3D<T> operator*(const TVector3D<T>& Vector);
    
    TVector2D<T> ToVector2D() const;
    TVector3D<T> ToVector3D() const;
private:
    void InitMatrixArray();
private:
    TArray<TArray<T>> Matrix;
};

#include "Matrix.inl"
