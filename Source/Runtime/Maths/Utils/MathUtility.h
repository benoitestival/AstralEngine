// ReSharper disable All
#pragma once
#include <complex>
#include <type_traits>

#define PI 3.14159f

#define DEGREE_TO_RADIAN(Value) (Value * PI / 180.0f)
#define RADIAN_TO_DEGREE(Value) (Value * 180.0f / PI)

template <typename T>
concept IsNumber = std::is_integral<T>::value || std::is_floating_point<T>::value;

struct FMath {
    template<IsNumber T>
    inline static T Sqrt(const T& Value) {
        return std::sqrt(Value);
    }

    template<IsNumber T>
    inline static T Pow(const T& Value, int Power) {
        return std::pow(Value, Power);
    }

    template<IsNumber T>
    inline static T Square(const T& Value) {
        return FMath::Pow(Value, 2);
    }

    template<IsNumber T>
    inline static float CosRad(const T& Value) {
        return std::cos(Value);
    }

    template<IsNumber T>
    inline static float SinRad(const T& Value) {
        return std::sin(Value);
    }

    template<IsNumber T>
    inline static float TanRad(const T& Value) {
        return std::tan(Value);
    }

    template<IsNumber T>
    inline static float ACosRad(const T& Value) {
        return std::acos(Value);
    }
    
    template<IsNumber T>
    inline static float ASinRad(const T& Value) {
        return std::tan(Value);
    }
    
    template<IsNumber T>
    inline static float ATanRad(const T& Value) {
        return std::tan(Value);
    }
};
