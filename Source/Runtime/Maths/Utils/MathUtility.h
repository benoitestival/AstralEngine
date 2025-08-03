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

    
    inline static double CosRad(const double& Value) {
        return std::cos(Value);
    }
    inline static float CosRad(const float& Value) {
        return std::cos(Value);
    }
    
    inline static double SinRad(const double& Value) {
        return std::sin(Value);
    }
    inline static float SinRad(const float& Value) {
        return std::sin(Value);
    }
    
    inline static double TanRad(const double& Value) {
        return std::tan(Value);
    }
    inline static float TanRad(const float& Value) {
        return std::tan(Value);
    }
    
    inline static double ACosRad(const double& Value) {
        return std::acos(Value);
    }
    inline static float ACosRad(const float& Value) {
        return std::acos(Value);
    }
   
    
    inline static double ASinRad(const double& Value) {
        return std::asin(Value);
    }
    inline static float ASinRad(const float& Value) {
        return std::asin(Value);
    }
   
    
    inline static double ATanRad(const double& Value) {
        return std::atan(Value);
    }
    inline static float ATanRad(const float& Value) {
        return std::atan(Value);
    }
    
    inline static double CosDeg(const double& Value) {
        return FMath::CosRad(DEGREE_TO_RADIAN(Value));
    }
    inline static float CosDeg(const float& Value) {
        return FMath::CosRad(DEGREE_TO_RADIAN(Value));
    }
    
    inline static double SinDeg(const double& Value) {
        return FMath::SinRad(DEGREE_TO_RADIAN(Value));
    }
    inline static float SinDeg(const float& Value) {
        return FMath::SinRad(DEGREE_TO_RADIAN(Value));
    }
    
    inline static double TanDeg(const double& Value) {
        return FMath::TanRad(DEGREE_TO_RADIAN(Value));
    }
    inline static float TanDeg(const float& Value) {
        return FMath::TanRad(DEGREE_TO_RADIAN(Value));
    }
    
    inline static double ACosDeg(const double& Value) {
        return RADIAN_TO_DEGREE(FMath::ACosRad(Value));
    }
    inline static float ACosDeg(const float& Value) {
        return RADIAN_TO_DEGREE(FMath::ACosRad(Value));
    }
    
    inline static double ASinDeg(const double& Value) {
        return RADIAN_TO_DEGREE(FMath::ASinRad(Value));
    }
    inline static float ASinDeg(const float& Value) {
        return RADIAN_TO_DEGREE(FMath::ASinRad(Value));
    }
    
    inline static double ATanDeg(const double& Value) {
        return RADIAN_TO_DEGREE(FMath::ATanRad(Value));
    }
    inline static float ATanDeg(const float& Value) {
        return RADIAN_TO_DEGREE(FMath::ATanRad(Value));
    }
}
