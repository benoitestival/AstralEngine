#pragma once
#include <valarray>


#define DECLARE_CONCRETE_MATH_TYPE(ConcreteName, GenericType)\
    using ConcreteName = GenericType;


template<typename T>
struct TVector2D {
    TVector2D(){};
    TVector2D(T XY) : X(XY), Y(XY){};
    TVector2D(T X_, T Y_) : X(X_), Y(Y_){};

    bool operator==(const TVector2D& Other) const{return X == Other.X && Y == Other.Y;};
    bool operator!=(const TVector2D& Other) const{return !(*this == Other);};

    TVector2D operator+(const TVector2D& Other) const {
        TVector2D Result = TVector2D();
        Result.X = X + Other.X;
        Result.Y = Y + Other.Y;
        return Result;
    };
    TVector2D operator-(const TVector2D& Other) const {
        TVector2D Result = TVector2D();
        Result.X = X - Other.X;
        Result.Y = Y - Other.Y;
        return Result;
    };
    TVector2D operator*(const TVector2D& Other) const {
        TVector2D Result = TVector2D();
        Result.X = X * Other.X;
        Result.Y = Y * Other.Y;
        return Result;
    };
    TVector2D operator/(const TVector2D& Other) const {
        TVector2D Result = TVector2D();
        Result.X = X / Other.X;
        Result.Y = Y / Other.Y;
        return Result;
    };

    TVector2D operator+(const T& Other) const {
        return *this + TVector2D(Other);
    }
    TVector2D operator-(const T& Other) const {
        return *this - TVector2D(Other);
    }
    TVector2D operator*(const T& Other) const {
        return *this * TVector2D(Other);
    }
    TVector2D operator/(const T& Other) const {
        return *this / TVector2D(Other);
    }

    void Normalize() {
        *this = *this/Lenght();
    };

    void SafeNormalize() {
        if (Lenght() > 0) {
            Normalize();
        }
    };
    
    float Lenght() {
        return std::sqrt(std::pow(X, 2) + std::pow(Y, 2));
    };
    
    float Dot(const TVector2D& Other) {
        return X * Other.X + Y * Other.Y;  
    };
    static float Dot(const TVector2D& A, const TVector2D& B) {
        return A.Dot(B);
    };

    
public:
    T X;
    T Y;
    
};

DECLARE_CONCRETE_MATH_TYPE(FVector2D, TVector2D<float>)
DECLARE_CONCRETE_MATH_TYPE(FIntVector2D, TVector2D<int>)