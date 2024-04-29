#pragma once
#include <vector>

#include "../Utils/Array.h"

template<typename T, int R, int C>
class TMatrix {
public:
    TMatrix() : RowNumbers(R), ColumnNumbers(C) {
        Matrix.assign(RowNumbers, TArray<T>().assign(ColumnNumbers));
    };
public:
    int RowNumbers = 0;
    int ColumnNumbers = 0;

private:
    TArray<TArray<T>> Matrix;
};

