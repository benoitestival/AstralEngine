// ReSharper disable All
#pragma once
#include <complex>
#include <type_traits>

#define PI 3.1415926535

#define DEGREE_TO_RADIAN(Value) (Value * PI / 180.0f)
#define RADIAN_TO_DEGREE(Value) (Value * 180.0f / PI)

template <typename T>
concept IsNumber = std::is_integral<T>::value || std::is_floating_point<T>::value;

struct FMath {
    template<IsNumber T>
    inline static double Sqrt(const T& Value) {
        return std::sqrt(Value);
    }

    template<IsNumber T>
    inline static double Pow(const T& Value, int Power) {
        return std::pow(Value, Power);
    }

    template<IsNumber T>
    inline static double Square(const T& Value) {
        return FMath::Pow(Value, 2);
    }

    template<IsNumber T>
    inline static double CosRad(const T& Value) {
        return std::cos(Value);
    }

    template<IsNumber T>
    inline static double SinRad(const T& Value) {
        return std::sin(Value);
    }

    template<IsNumber T>
    inline static double TanRad(const T& Value) {
        return std::tan(Value);
    }

    template<IsNumber T>
    inline static double ACosRad(const T& Value) {
        return std::acos(Value);
    }
    
    template<IsNumber T>
    inline static double ASinRad(const T& Value) {
        return std::tan(Value);
    }
    
    template<IsNumber T>
    inline static double ATanRad(const T& Value) {
        return std::tan(Value);
    }

    template<IsNumber T>
    inline static double CosDeg(const T& Value) {
        return FMath::CosRad(DEGREE_TO_RADIAN(Value));
    }

    template<IsNumber T>
    inline static double SinDeg(const T& Value) {
        return FMath::SinRad(DEGREE_TO_RADIAN(Value));
    }

    template<IsNumber T>
    inline static double TanDeg(const T& Value) {
        return FMath::TanRad(DEGREE_TO_RADIAN(Value));
    }

    template<IsNumber T>
    inline static double ACosDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ACosRad(Value));
    }

    template<IsNumber T>
    inline static double ASinDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ASinRad(Value));
    }

    template<IsNumber T>
    inline static double ATanDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ATanRad(Value));
    }
};
