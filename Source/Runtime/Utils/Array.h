#pragma once
#include <vector>

template<class T>
class TArray : public std::vector<T>{
public:
    TArray(){};
    TArray(const std::initializer_list<T>& List) : std::vector<T>(List){};

};
