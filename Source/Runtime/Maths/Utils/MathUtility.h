// ReSharper disable All
#pragma once
#include <cmath>
#include <type_traits>

#define PI 3.1415926535

#define DEGREE_TO_RADIAN(Value) (Value * PI / 180.0f)
#define RADIAN_TO_DEGREE(Value) (Value * 180.0f / PI)

template <typename T>
concept IsNumber = std::is_integral<T>::value || std::is_floating_point<T>::value;

template <typename T>
concept IsFloatingPoint = std::is_floating_point<T>::value;

struct FMath {
    template<IsFloatingPoint T>
    inline static T Sqrt(const T& Value) {
        return std::sqrt(Value);
    }

    template<IsFloatingPoint T>
    inline static T Pow(const T& Value, const T& Power) {
        return std::pow(Value, Power);
    }

    template<IsFloatingPoint T>
    inline static T Square(const T& Value) {
        return FMath::Pow(Value, 2);
    }


    template<IsFloatingPoint T>
    inline static T CosRad(const T& Value) {
        return std::cos(Value);
    }

    template<IsFloatingPoint T>
    inline static T SinRad(const T& Value) {
        return std::sin(Value);
    }

    template<IsFloatingPoint T>
    inline static T TanRad(const T& Value) {
        return std::tan(Value);
    }
    
    template<IsFloatingPoint T>
    inline static T ACosRad(const T& Value) {
        return std::acos(Value);
    }
   
    template<IsFloatingPoint T>
    inline static T ASinRad(const T& Value) {
        return std::asin(Value);
    }
   
    template<IsFloatingPoint T>
    inline static T ATanRad(const T& Value) {
        return std::atan(Value);
    }


    template<IsFloatingPoint T>
    inline static T CosDeg(const T& Value) {
        return FMath::CosRad(DEGREE_TO_RADIAN(Value));
    }

    
    template<IsFloatingPoint T>
    inline static T SinDeg(const T& Value) {
        return FMath::SinRad(DEGREE_TO_RADIAN(Value));
    }
    
    template<IsFloatingPoint T>
    inline static T TanDeg(const T& Value) {
        return FMath::TanRad(DEGREE_TO_RADIAN(Value));
    }

    template<IsFloatingPoint T>
    inline static T ACosDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ACosRad(Value));
    }
    
    template<IsFloatingPoint T>
    inline static T ASinDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ASinRad(Value));
    }
    
    template<IsFloatingPoint T>
    inline static T ATanDeg(const T& Value) {
        return RADIAN_TO_DEGREE(FMath::ATanRad(Value));
    }

};
