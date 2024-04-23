// ReSharper disable CppFunctionDoesntReturnValue
#pragma once
#include <sstream>
#include <string>

template<class T>
struct HasOstreamOperator {
    template<class V>
    static auto test(V*) -> decltype(std::declval<std::ostream>() << std::declval<V>()) {};
    template<typename W>
    static auto test(...) -> std::false_type {};
    static constexpr bool value = std::is_same<std::ostream&, decltype(test<T>(0))>::value;
};

template<class T>
struct HasIstreamOperator {
    template<class V>
    static auto test(V*) -> decltype(std::declval<std::istream>() >> std::declval<V>()) {};
    template<typename W>
    static auto test(...) -> std::false_type {};
    static constexpr bool value = std::is_same<std::istream&, decltype(test<T>(0))>::value;
};

template<class T>
static constexpr bool SupportStreamOperator(){
    return HasOstreamOperator<T>::value && HasIstreamOperator<T>::value;
};

template <typename T>
concept SupportSerialization = SupportStreamOperator<T>();

template<SupportSerialization T>
class SerializeType {
public:
    //String Handling
    std::string ToString(T Data) {
        std::string OutputString = std::string();
        return std::stringstream(OutputString) << Data;
    };
    T FromString(std::string String) {
        T OutData = T();
        return std::stringstream(String) >> OutData;
    };

    //Binary Handling
    //TODO 
};

//////////////////Specialisation template exemple//////////////////////
//
//Specialisation for handling bool
// template<>
// inline std::string SerializeType<bool>::ToString(bool Data) {
//     return Data ? "true" : "false";
// };
// template<>
// inline bool SerializeType<bool>::FromString(std::string String) {
//     return String == "true" ? true : false;
// }
