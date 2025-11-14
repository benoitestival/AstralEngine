#pragma once


template<typename T, int Size>
struct TVector {
    TVector() = default;

    bool operator==(const TVector<T, Size>& Other) const {
        bool Result = true;
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            if (Datas[CoordIndex] != Other[CoordIndex]) {
                Result = false;
            }
        }
        return Result;
    }
    bool operator!=(const TVector<T, Size>& Other) const {
        return !(*this) == Other;
    }
    
    TVector<T, Size> operator+(const TVector<T, Size>& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] + Other[CoordIndex];
        }
        return Result;
    }
    TVector<T, Size> operator-(const TVector<T, Size>& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] - Other[CoordIndex];
        }
        return Result;
    }
    TVector<T, Size> operator*(const TVector<T, Size>& Other) {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] * Other[CoordIndex];
        }
        return Result;
    }
    TVector<T, Size> operator/(const TVector<T, Size>& Other) {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] / Other[CoordIndex];
        }
        return Result;
    }

    TVector<T, Size> operator+(const T& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] + Other;
        }
        return Result;
    }
    TVector<T, Size> operator-(const T& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] - Other;
        }
        return Result;
    }
    TVector<T, Size> operator*(const T& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] * Other;
        }
        return Result;
    }
    TVector<T, Size> operator/(const T& Other) const {
        TVector<T, Size> Result = TVector();
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            Result[CoordIndex] = Datas[CoordIndex] / Other;
        }
        return Result;
    }

    T& operator[](int Index) const {
        return Datas[Index];
    }

    const T& operator[](int Index){
        return Datas[Index];
    }

    //Matrix conversion

    float Dot(const TVector<T, Size>& Other) {
        float DotResult = 0.0f;
        for (int CoordIndex = 0; CoordIndex < Size; CoordIndex++) {
            DotResult += static_cast<float>(Datas[CoordIndex]) * static_cast<float>(Other[CoordIndex]);
        }
        return DotResult;
    }
    
    
private:
    T Datas[Size];
};