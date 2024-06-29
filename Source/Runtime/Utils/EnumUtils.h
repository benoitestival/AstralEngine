#pragma once
#include "TemplateUtils.h"
//
// template <typename T>
// concept IsBitFlagTestable = IsPrimaryType<T>();

class EnumUtils {
public:
    template<typename EnumType>
    static bool HasFlag(const EnumType Flag, int& Flags){
        return (Flags & static_cast<int>(Flag)) != 0; 
    }

    template<typename EnumType>
    static bool DoesntHasFlag(const EnumType Flag, int& Flags){
        return !HasFlag(Flag, Flags); 
    }

    template<typename EnumType>
    static void AddFlag(const EnumType Flag, int& Flags){
        Flags = Flags | static_cast<int>(Flag);
    }

    template<typename EnumType>
    static void RemoveFlag(const EnumType Flag, int& Flags){
        Flags = Flags & (~static_cast<int>(Flag));
    }
};
