#pragma once
#include <vector>

template<typename T, int R, int C>
class TMatrix {
public:
    TMatrix() : RowNumbers(R), ColumnNumbers(C) {
        Matrix.assign(RowNumbers, std::vector<T>().assign(ColumnNumbers));
    };
public:
    int RowNumbers = 0;
    int ColumnNumbers = 0;

private:
    std::vector<std::vector<T>> Matrix;
};

