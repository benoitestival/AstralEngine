#pragma once
#include <type_traits>

template<class TypeA, class TypeB>
static constexpr bool IsConstructible(){
    return std::is_constructible<TypeA, TypeB>::value;
};

template<class TypeA, class TypeB>
static constexpr bool IsConvertible(){
    return std::is_convertible<TypeA, TypeB>::value;
};

template<class TypeA, class TypeB>
static constexpr bool IsExplicitConvertible(){
    return IsConstructible<TypeA, TypeB>() && !IsConvertible<TypeB, TypeA>();
};

template<class T>
static constexpr bool IsPointer() {
    return std::is_pointer<T>::value;
}

template<class T>
static constexpr bool IsPrimaryType() {
    return std::is_integral<T>::value || std::is_floating_point<T>::value;
}

template<class T>
static bool IsAstralObject() {
    return false;
}


// template<class Type>
// using WriteOsStream = decltype(std::declval<std::ostringstream>() << std::declval<Type>());