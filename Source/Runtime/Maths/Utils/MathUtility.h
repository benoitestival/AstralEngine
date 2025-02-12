#pragma once
#include <complex>
#include <type_traits>

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
};
